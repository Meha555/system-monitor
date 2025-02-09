#pragma once

#include <string>
#include <unordered_map>

#include "monitor_inter.h"

#include "monitor_info.pb.h"

namespace monitor
{
class CpuStatMonitor : public MonitorInter
{
    struct CpuStat
    {
        std::string name;
        float user;
        float system;
        float idle;
        float nice;
        float io_wait;
        float irq;
        float soft_irq;
        float steal;
        float guest;
        float guest_nice;
    };

public:
    static constexpr char kStatFile[] = "/proc/stat";
    explicit CpuStatMonitor() = default;
    void UpdateOnce(monitor::proto::MonitorInfo *monitor_info) override;
    void Stop() override;

private:
    std::unordered_map<std::string, std::unique_ptr<CpuStat>> m_cpu_stat_map;
};

} // namespace monitor
