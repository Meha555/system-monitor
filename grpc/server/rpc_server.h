#pragma once

#include <optional>

#include <grpcpp/support/status.h>

#include "monitor_info.pb.h"
#include "monitor_service.grpc.pb.h"
#include "monitor_service.pb.h"

namespace monitor
{
class MonitorServiceImpl : public monitor::proto::MonitorService::Service
{
public:
    ::grpc::Status SetMonitorInfo(::grpc::ServerContext *context,
                                  const ::monitor::proto::MonitorInfo *request,
                                  ::google::protobuf::Empty *response) override;
    ::grpc::Status GetMonitorInfo(::grpc::ServerContext *context,
                                  const ::google::protobuf::Empty *request,
                                  ::monitor::proto::GetMonitorInfoResponse *response) override;

private:
    // 使用对象而非指针，确保了 m_monitor_info 的内容是通过深拷贝方式更新的，避免了潜在的内存管理和线程安全问题。
    std::optional<monitor::proto::MonitorInfo> m_monitor_info;
};

} // namespace monitor
