#!/bin/bash

protoc -I ../../proto cpu_load.proto --go_out=proto --go-grpc_out=proto
protoc -I ../../proto cpu_softirq.proto --go_out=proto --go-grpc_out=proto
protoc -I ../../proto cpu_stat.proto --go_out=proto --go-grpc_out=proto
protoc -I ../../proto mem_info.proto --go_out=proto --go-grpc_out=proto
protoc -I ../../proto monitor_service.proto --go_out=proto --go-grpc_out=proto
protoc -I ../../proto monitor_info.proto --go_out=proto --go-grpc_out=proto
protoc -I ../../proto net_info.proto --go_out=proto --go-grpc_out=proto