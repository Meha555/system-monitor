package server

import (
	"context"
	"sync"

	pb "monitor-broker/proto"
	"google.golang.org/protobuf/types/known/emptypb"
)

type MonitorManagementServerImpl struct {
	pb.UnimplementedMonitorManagementServiceServer // 继承自动生成的 Unimplemented 方法，可以确保将来不破坏接口兼容性

	mu           sync.Mutex      // 添加互斥锁以保护 Monitor_info
	MonitorInfos []*pb.MonitorInfo
	capacity int
}

func (s *MonitorManagementServerImpl) SetMonitorInfo(ctx context.Context, req *pb.MonitorInfo) (*emptypb.Empty, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	if len(s.MonitorInfos) >= s.capacity {
		s.MonitorInfos = s.MonitorInfos[1:]
	}
	s.MonitorInfos = append(s.MonitorInfos, req)
	return &emptypb.Empty{}, nil
}

func (s *MonitorManagementServerImpl) GetMonitorInfo(ctx context.Context, req *emptypb.Empty) (*pb.MonitorInfo, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	if len(s.MonitorInfos) == 0 {
		return &pb.MonitorInfo{}, nil
	}
	return s.MonitorInfos[len(s.MonitorInfos)-1], nil
}

func NewMonitorManagementServer(capacity int) *MonitorManagementServerImpl {
	return &MonitorManagementServerImpl{
		MonitorInfos: make([]*pb.MonitorInfo, 0),
		capacity: capacity,
	}
}