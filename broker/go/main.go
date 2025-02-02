package main

import (
	"log"
	"net"
	"flag"
	"gopkg.in/ini.v1"
	"google.golang.org/grpc"
	pb "monitor-broker/proto"
	"monitor-broker/server"
)

var confFile string

func init() {
	flag.StringVar(&confFile, "conf", "monitor.conf", "Server config file")
}

func main() {
	flag.Parse()

	cfg, err := ini.Load(confFile)
	if err != nil {
		log.Fatal("Failed to load: ", confFile)
	}

	serverAddr := cfg.Section("server").Key("ip").String() + ":" + cfg.Section("server").Key("port").String()

	lis, err := net.Listen("tcp", serverAddr)
	if err != nil {
		panic(err)
	}
	s := grpc.NewServer()
	// server := server.NewMonitorServer()
	server := server.NewMonitorManagementServer(10)
	pb.RegisterMonitorManagementServiceServer(s, server)
	err = s.Serve(lis)
	if err != nil {
		panic(err)
	}
}
