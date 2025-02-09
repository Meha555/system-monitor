#pragma once

#include <chrono>
#include <string>
#include <unordered_map>

#include "monitor_inter.h"

#include "monitor_info.pb.h"

namespace monitor
{
class NetMonitor : public MonitorInter
{
    struct NetInfo
    {
        std::string name;
        int64_t rcv_bytes;
        int64_t rcv_packets;
        int64_t rcv_err;
        int64_t rcv_drop;
        int64_t snd_bytes;
        int64_t snd_packets;
        int64_t snd_err;
        int64_t snd_drop;
        std::chrono::steady_clock::time_point timepoint;
    };

public:
    static constexpr char kNetFile[] = "/proc/net/dev";
    explicit NetMonitor() = default;
    void UpdateOnce(monitor::proto::MonitorInfo *monitor_info) override;
    void Stop() override;

private:
    std::unordered_map<std::string, std::unique_ptr<NetInfo>> m_net_info_map;
};

} // namespace monitor