#include "rpc_client.h"
#include "monitor_service.grpc.pb.h"
#include <glog/logging.h>

namespace monitor
{
RpcClient::RpcClient(const std::string &server_address, const std::shared_ptr<grpc::ChannelCredentials>& creds)
    : m_channel(grpc::CreateChannel(server_address, creds))
{
}

MonitorManagementClient::MonitorManagementClient(const std::string &server_address,
                                                   const std::shared_ptr<grpc::ChannelCredentials>& creds)
    : RpcClient(server_address, creds)
{
    m_stub = monitor::proto::MonitorManagementService::NewStub(m_channel);
}

bool MonitorManagementClient::SetMonitorInfo(const monitor::proto::MonitorInfo &monito_info)
{
    grpc::ClientContext context;
    google::protobuf::Empty response;
    grpc::Status status = m_stub->SetMonitorInfo(&context, monito_info, &response);
    if (status.ok()) {
        // LOG(INFO) << "SetMonitorInfo: " << monito_info.ShortDebugString();
        return true;
    } else {
        LOG(ERROR) << "status.error_details: " << status.error_details();
        LOG(ERROR) << "status.error_message: " << status.error_message();
        return false;
    }
}

bool MonitorManagementClient::GetMonitorInfo(monitor::proto::MonitorInfo *monito_info)
{
    grpc::ClientContext context;
    google::protobuf::Empty request;
    grpc::Status status = m_stub->GetMonitorInfo(&context, request, monito_info);
    if (status.ok()) {
        // LOG(INFO) << "GetMonitorInfo: " << monito_info->ShortDebugString();
        return true;
    } else {
        LOG(ERROR) << "status.error_details: " << status.error_details();
        LOG(ERROR) << "status.error_message: " << status.error_message();
        return false;
    }
}

MonitorClient::MonitorClient(const std::string &server_address,
                             const std::shared_ptr<grpc::ChannelCredentials>& creds)
    : RpcClient(server_address, creds)
{
    m_stub = monitor::proto::MonitorService::NewStub(m_channel);
}

MonitorClient::~MonitorClient()
{
}

bool MonitorClient::PublishMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    grpc::ClientContext context;
    google::protobuf::Empty response;
    grpc::Status status = m_stub->PublishMonitorInfo(&context, monitor_info, &response);
    if (status.ok()) {
        // LOG(INFO) << "PublishMonitorInfo: " << monitor_info.ShortDebugString();
        return true;
    } else {
        LOG(ERROR) << "status.error_details: " << status.error_details();
        LOG(ERROR) << "status.error_message: " << status.error_message();
        return false;
    }
}

bool MonitorClient::SubscribeMonitorInfo()
{
    LOG(INFO) << "SubscribeMonitorInfo";
    grpc::ClientContext context;
    google::protobuf::Empty request;
    std::unique_ptr<grpc::ClientReader<monitor::proto::MonitorInfo>> reader(
        m_stub->SubscribeMonitorInfo(&context, request));

    auto info = std::make_shared<monitor::proto::MonitorInfo>();
    while (reader->Read(info.get())) {
        // LOG(INFO) << "Received monitor info: " << info->ShortDebugString();
        std::unique_lock lock(m_mutex);
        if (m_monitor_infos.size() >= s_capacity) {
            m_monitor_infos.pop_front();
        }
        m_monitor_infos.emplace_back(info);
        m_cond.notify_one();
    }
    const grpc::Status status = reader->Finish();
    if (!status.ok()) {
        LOG(INFO) << "Received all monitor info";
        return true;
    } else {
        LOG(ERROR) << "Subscription failed: " << status.error_message();
        return false;
    }
}

const monitor::proto::MonitorInfo MonitorClient::FetchMonitorInfo() const
{
    std::shared_lock lock(m_mutex);
    m_cond.wait(lock, [this] { return !m_monitor_infos.empty(); });
    return *m_monitor_infos.back();
}

} // namespace monitor
