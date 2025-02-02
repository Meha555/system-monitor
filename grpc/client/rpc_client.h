#pragma once

#include <condition_variable>
#include <deque>
#include <shared_mutex>

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
    RpcClient(const std::string &server_address, const std::shared_ptr<grpc::ChannelCredentials>& creds = grpc::InsecureChannelCredentials());
    virtual ~RpcClient() = default;

protected:
    std::shared_ptr<grpc::Channel> m_channel;
};

class MonitorManagementClient final : public RpcClient
{
public:
    MonitorManagementClient(const std::string &server_address, const std::shared_ptr<grpc::ChannelCredentials>& creds = grpc::InsecureChannelCredentials());

    bool SetMonitorInfo(const monitor::proto::MonitorInfo &monito_info);
    bool GetMonitorInfo(monitor::proto::MonitorInfo *monito_info);

private:
    std::unique_ptr<monitor::proto::MonitorManagementService::Stub> m_stub;
};

class MonitorClient final : public RpcClient
{
    static constexpr size_t s_capacity = 3; // 数量不需要太大，只需确保订阅者消费期间数据不丢失即可（虽然我用了shared_ptr）
public:
    MonitorClient(const std::string &server_address, const std::shared_ptr<grpc::ChannelCredentials>& creds = grpc::InsecureChannelCredentials());
    ~MonitorClient();

    bool PublishMonitorInfo(const monitor::proto::MonitorInfo &monitor_info);
    bool SubscribeMonitorInfo();

    const monitor::proto::MonitorInfo FetchMonitorInfo() const;

private:
    std::unique_ptr<monitor::proto::MonitorService::Stub> m_stub;
    mutable std::shared_mutex m_mutex;
    mutable std::condition_variable_any m_cond;
    std::deque<std::shared_ptr<monitor::proto::MonitorInfo>> m_monitor_infos;
};

} // namespace monitor
