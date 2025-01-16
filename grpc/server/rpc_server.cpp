#include "rpc_server.h"

namespace monitor
{
::grpc::Status MonitorServiceImpl::SetMonitorInfo(
    ::grpc::ServerContext *context,
    const ::monitor::proto::MonitorInfo *request,
    ::google::protobuf::Empty *response)
{
    m_monitor_infos.Clear();
    m_monitor_infos = *request;
    return grpc::Status::OK;
}

::grpc::Status MonitorServiceImpl::GetMonitorInfo(
    ::grpc::ServerContext *context, const ::google::protobuf::Empty *request,
    ::monitor::proto::MonitorInfo *response)
{
    *response = m_monitor_infos;
    return grpc::Status::OK;
}

} // namespace monitor
