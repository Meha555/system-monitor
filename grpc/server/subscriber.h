#include "monitor_service.grpc.pb.h"

class Subscriber {
public:
    virtual ~Subscriber() = default;
    virtual bool Send(const monitor::proto::MonitorInfo& event) = 0;
};

class StreamingSubscriber : public Subscriber {
public:
    StreamingSubscriber(grpc::ServerWriter<monitor::proto::MonitorInfo>* writer) : m_writer(writer) {}

    bool Send(const monitor::proto::MonitorInfo& event) override {
        return m_writer->Write(event); // 同步发送（实际生产环境建议异步）
    }

    grpc::ServerWriter<monitor::proto::MonitorInfo>* writer() const {
        return m_writer;
    }

private:
    grpc::ServerWriter<monitor::proto::MonitorInfo>* m_writer;
};