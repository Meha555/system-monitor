#include "rpc_server.h"
#include <thread>

namespace monitor
{
MonitorManagementServiceImpl::MonitorManagementServiceImpl(size_t capacity)
    : m_capacity(capacity)
{
}

grpc::Status MonitorManagementServiceImpl::SetMonitorInfo(
    grpc::ServerContext *context,
    const ::monitor::proto::MonitorInfo *request,
    google::protobuf::Empty *response)
{
    std::unique_lock lock(m_mutex);
    if (m_monitor_infos.size() >= m_capacity) {
        m_monitor_infos.pop_front();
    }
    m_monitor_infos.push_back(*request);
    return grpc::Status::OK;
}

grpc::Status MonitorManagementServiceImpl::GetMonitorInfo(
    grpc::ServerContext *context, const google::protobuf::Empty *request,
    ::monitor::proto::MonitorInfo *response)
{
    std::shared_lock lock(m_mutex);
    if (!m_monitor_infos.empty()) {
        *response = m_monitor_infos.front();
    } else {
        *response = monitor::proto::MonitorInfo();
    }
    return grpc::Status::OK;
}

grpc::Status MonitorServiceImpl::SubscribeMonitorInfo(grpc::ServerContext* context,
                                    const google::protobuf::Empty* request,
                                    grpc::ServerWriter< ::monitor::proto::MonitorInfo>* writer)
{
    {
        std::unique_lock lock(m_mutex);
        m_subscribers.emplace_back(std::make_unique<StreamingSubscriber>(writer));
    }

    // 阻塞直到客户端断开连接
    while (!context->IsCancelled()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // 客户端断开时清理
    std::unique_lock lock(m_mutex);
    m_subscribers.erase(
        std::remove_if(m_subscribers.begin(), m_subscribers.end(),
            [writer](const std::unique_ptr<Subscriber>& sub) {
                return dynamic_cast<StreamingSubscriber*>(sub.get())->writer() == writer;
            }),
        m_subscribers.end());
    return grpc::Status::OK;
}
grpc::Status MonitorServiceImpl::PublishMonitorInfo(grpc::ServerContext* context,
                                    const ::monitor::proto::MonitorInfo* request,
                                    google::protobuf::Empty* response)
{
    std::shared_lock lock(m_mutex);
    for (auto& subscriber : m_subscribers) {
        if (!subscriber->Send(*request)) {
            context->TryCancel();
        }
    }
    return grpc::Status::OK;
}

} // namespace monitor
