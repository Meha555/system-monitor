package main

import (
	"context"
	"log"
	"net"
	"sync"
	"flag"
	"gopkg.in/ini.v1"
	"google.golang.org/grpc"
	pb "monitor-broker/proto"
	emptypb "google.golang.org/protobuf/types/known/emptypb"
)

type Server struct {
	pb.UnimplementedMonitorServiceServer // 继承自动生成的 Unimplemented 方法，可以确保将来不破坏接口兼容性

	mu            sync.Mutex              // 添加互斥锁以保护 monitor_info
	monitor_info *pb.MonitorInfo          // 使用指针而不是值
}

func (s *Server) SetMonitorInfo(ctx context.Context, req *pb.MonitorInfo) (*emptypb.Empty, error) {
	s.mu.Lock()
	defer s.mu.Unlock()
	s.monitor_info = req
	return &emptypb.Empty{}, nil
}

func (s *Server) GetMonitorInfo(ctx context.Context, req *emptypb.Empty) (*pb.GetMonitorInfoResponse, error) {
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

var confFile string

func init() {
	flag.StringVar(&confFile, "conf", "monitor.conf", "Server config file")
}

func main() {
	flag.Parse()

	cfg, err := ini.Load(confFile)
	if (err != nil) {
		log.Fatal("Failed to load: ", confFile)
	}

	serverAddr := cfg.Section("server").Key("ip").String() + ":" + cfg.Section("server").Key("port").String()

	lis, err := net.Listen("tcp", serverAddr)
	if err != nil {
		panic(err)
	}
	s := grpc.NewServer()
	server := &Server{
		monitor_info: &pb.MonitorInfo{}, // 初始化为非 nil
	}
	pb.RegisterMonitorServiceServer(s, server)
	log.Println("Server listening at TCP ", serverAddr)
	err = s.Serve(lis)
	if err != nil {
		panic(err)
	}
}