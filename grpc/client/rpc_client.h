#pragma once

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/grpcpp.h>

#include "monitor_info.pb.h"
#include "monitor_service.grpc.pb.h"

namespace monitor
{
class RpcClient
{
public:
    RpcClient(const std::string &server_address);
    ~RpcClient() = default;
    bool SetMonitorInfo(const monitor::proto::MonitorInfo &monito_info);
    bool GetMonitorInfo(monitor::proto::MonitorInfo *monito_info);

private:
    std::unique_ptr<monitor::proto::MonitorService::Stub> m_stub;
};
} // namespace monitor
