#pragma once

#include <chrono>
#include <string>
#include <unordered_map>

#include "monitor_info.pb.h"
#include "monitor_inter.h"

namespace monitor
{
class CpuSoftIrqMonitor : public MonitorInter
{
    struct SoftIrq
    {
        std::string name;
        int64_t hi;
        int64_t timer;
        int64_t net_tx;
        int64_t net_rx;
        int64_t block;
        int64_t irq_poll;
        int64_t tasklet;
        int64_t sched;
        int64_t hrtimer;
        int64_t rcu;
        std::chrono::steady_clock::time_point timepoint;
    };

public:
    static constexpr char kSoftIrqFile[] = "/proc/softirqs";
    explicit CpuSoftIrqMonitor() = default;

    void UpdateOnce(monitor::proto::MonitorInfo *monitor_info) override;
    void Stop() override;

private:
    std::unordered_map<std::string, std::unique_ptr<SoftIrq>> m_cpu_softirqs_map;
};

} // namespace monitor
