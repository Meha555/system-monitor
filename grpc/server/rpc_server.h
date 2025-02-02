#pragma once

#include <deque>
#include <shared_mutex>
#include <grpcpp/support/status.h>

#include "monitor_info.pb.h"
#include "monitor_service.grpc.pb.h"
#include "subscriber.h"

namespace monitor
{
class MonitorManagementServiceImpl final : public monitor::proto::MonitorManagementService::Service
{
public:
    explicit MonitorManagementServiceImpl(size_t capacity = 10);

    grpc::Status SetMonitorInfo(grpc::ServerContext *context,
                                  const ::monitor::proto::MonitorInfo *request,
                                  google::protobuf::Empty *response) override;
    grpc::Status GetMonitorInfo(grpc::ServerContext *context,
                                  const google::protobuf::Empty *request,
                                  ::monitor::proto::MonitorInfo *response) override;

private:
    // 使用对象而非指针，确保了 m_monitor_infos 的内容是通过深拷贝方式更新的，避免了潜在的内存管理和线程安全问题。
    size_t m_capacity;
    std::deque<monitor::proto::MonitorInfo> m_monitor_infos;
    mutable std::shared_mutex m_mutex;
};

class MonitorServiceImpl final : public monitor::proto::MonitorService::Service {
public:
    grpc::Status SubscribeMonitorInfo(grpc::ServerContext* context,
                                        const google::protobuf::Empty* request,
                                        grpc::ServerWriter< ::monitor::proto::MonitorInfo>* writer) override;
    grpc::Status PublishMonitorInfo(grpc::ServerContext* context,
                                      const ::monitor::proto::MonitorInfo* request,
                                      google::protobuf::Empty* response) override;

private:
    std::vector<std::unique_ptr<Subscriber>> m_subscribers;
    mutable std::shared_mutex m_mutex;
};

} // namespace monitor
