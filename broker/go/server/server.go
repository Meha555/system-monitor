package server

import (
	"context"
	"sync"
	pb "monitor-broker/proto"
	emptypb "google.golang.org/protobuf/types/known/emptypb"
)


type MonitorServiceServer struct {
	pb.UnimplementedMonitorServiceServer // 继承自动生成的 Unimplemented 方法，可以确保将来不破坏接口兼容性

	mu            sync.Mutex              // 添加互斥锁以保护 monitor_info
	monitor_info *pb.MonitorInfo          // 使用指针而不是值
}

func (s *MonitorServiceServer) SetMonitorInfo(ctx context.Context, req *pb.MonitorInfo) (*emptypb.Empty, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.monitor_info = req
	return &emptypb.Empty{}, nil
}

func (s *MonitorServiceServer) GetMonitorInfo(ctx context.Context, req *emptypb.Empty) (*pb.GetMonitorInfoResponse, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	if s.monitor_info == nil {
		return NewGetMonitorInfoResponse(false, nil), nil
	}
	return NewGetMonitorInfoResponse(true, s.monitor_info), nil
}

func NewGetMonitorInfoResponse(success bool, monitorInfo *pb.MonitorInfo) *pb.GetMonitorInfoResponse {
	return &pb.GetMonitorInfoResponse{
		Result:     &pb.Result{Success: success},
		MonitorInfo: monitorInfo,
	}
}

func NewMonitorServiceServer() *MonitorServiceServer {
	return &MonitorServiceServer{
		monitor_info: &pb.MonitorInfo{},
	}
}