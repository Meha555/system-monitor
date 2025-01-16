#pragma once

#include "monitor_inter.h"

#include "monitor_info.pb.h"

namespace monitor
{
class CpuLoadMonitor : public MonitorInter
{
    struct CpuLoad
    {
        float load_avg_1m;
        float load_avg_3m;
        float load_avg_15m;
    };

public:
    static constexpr char kLoadAvgFile[] = "/proc/loadavg";
    explicit CpuLoadMonitor() = default;
    void UpdateOnce(monitor::proto::MonitorInfo *monitor_info) override;
    void Stop() override;

private:
    std::shared_ptr<CpuLoad> m_load;
};

} // namespace monitor
