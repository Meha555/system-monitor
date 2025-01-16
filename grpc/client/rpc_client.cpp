#include "rpc_client.h"
#include <glog/logging.h>

namespace monitor
{
RpcClient::RpcClient(const std::string &server_address)
{
    auto channel = grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials());
    m_stub = monitor::proto::MonitorService::NewStub(channel);
}

bool RpcClient::SetMonitorInfo(const monitor::proto::MonitorInfo &monito_info)
{
    ::grpc::ClientContext context;
    ::google::protobuf::Empty response;
    ::grpc::Status status = m_stub->SetMonitorInfo(&context, monito_info, &response);
    if (status.ok()) {
        LOG(INFO) << "SetMonitorInfo: " << monito_info.ShortDebugString();
        return true;
    } else {
        LOG(ERROR) << "status.error_details: " << status.error_details();
        LOG(ERROR) << "status.error_message: " << status.error_message();
        return false;
    }
}

bool RpcClient::GetMonitorInfo(monitor::proto::MonitorInfo *monito_info)
{
    ::grpc::ClientContext context;
    ::google::protobuf::Empty request;
    ::grpc::Status status = m_stub->GetMonitorInfo(&context, request, monito_info);
    if (status.ok()) {
        LOG(INFO) << "GetMonitorInfo: " << monito_info->ShortDebugString();
        return true;
    } else {
        LOG(ERROR) << "status.error_details: " << status.error_details();
        LOG(ERROR) << "status.error_message: " << status.error_message();
        return false;
    }
}
} // namespace monitor
