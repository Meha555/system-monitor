#include "rpc_server.h"

namespace monitor
{
::grpc::Status MonitorServiceImpl::SetMonitorInfo(
    ::grpc::ServerContext *context,
    const ::monitor::proto::MonitorInfo *request,
    ::google::protobuf::Empty *response)
{
    if (m_monitor_info) {
        (*m_monitor_info).Clear();
    }
    m_monitor_info = *request;
    return grpc::Status::OK;
}

::grpc::Status MonitorServiceImpl::GetMonitorInfo(
    ::grpc::ServerContext *context, const ::google::protobuf::Empty *request,
    ::monitor::proto::GetMonitorInfoResponse *response)
{
    if (!m_monitor_info) {
        response->mutable_result()->set_success(false);
    } else {
        response->mutable_result()->set_success(true);
        response->mutable_monitor_info()->CopyFrom(*m_monitor_info);
    }
    return grpc::Status::OK;
}

} // namespace monitor
