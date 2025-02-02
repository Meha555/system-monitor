package server

import (
	"context"
	"log"
	"sync"

	pb "monitor-broker/proto"

	"google.golang.org/grpc"
	"google.golang.org/protobuf/types/known/emptypb"
)

type MonitorServerImpl struct {
	pb.UnimplementedMonitorServiceServer

	mu sync.Mutex // 添加互斥锁以保护 subscribers
	subscribers []chan *pb.MonitorInfo
}

func (s *MonitorServerImpl) SubscribeMonitorInfo(req *emptypb.Empty, stream grpc.ServerStreamingServer[pb.MonitorInfo]) error {
	// 为当前订阅者创建消息通道
	eventChan := make(chan *pb.MonitorInfo, 10)

	// 注册订阅者
	s.mu.Lock()
	s.subscribers = append(s.subscribers, eventChan)
	s.mu.Unlock()

	defer func() {
		// 客户端断开时注销
		s.mu.Lock()
		defer s.mu.Unlock()
		for i, ch := range s.subscribers {
			if ch == eventChan {
				s.subscribers = append(s.subscribers[:i], s.subscribers[i+1:]...)
				break
			}
		}
		close(eventChan)
	}()

	// 持续监听通道并发送事件
	for {
		select {
		case event, ok := <-eventChan:
			if !ok {
				return nil
			}
			if err := stream.Send(event); err != nil {
				return err
			}
		case <-stream.Context().Done():
			return stream.Context().Err()
		}
	}
}

func (s *MonitorServerImpl) PublishMonitorInfo(ctx context.Context, req *pb.MonitorInfo) (*emptypb.Empty, error) {
	// 广播消息给所有订阅者
	s.mu.Lock()
	defer s.mu.Unlock()
	for _, ch := range s.subscribers {
		select {
		case ch <- req: // 非阻塞发送
		default:
			log.Println("Subscriber channel full, dropping message")
		}
	}
	return &emptypb.Empty{}, nil
}

func NewMonitorServer() *MonitorServerImpl {
	return &MonitorServerImpl{
		subscribers: []chan *pb.MonitorInfo{},
	}
}