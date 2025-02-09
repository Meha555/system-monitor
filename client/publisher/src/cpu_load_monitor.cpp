#include "cpu_load_monitor.h"
#include "utils.h"

#include <glog/logging.h>

#include "monitor_info.pb.h"

namespace monitor
{
void CpuLoadMonitor::UpdateOnce(monitor::proto::MonitorInfo *monitor_info)
{
    std::vector<std::string> cpu_load;
    if (!Utils::ReadLine(kLoadAvgFile, cpu_load)) {
        LOG(ERROR) << "Read " << kLoadAvgFile << " failed";
        return;
    }
    if (!m_load) {
        m_load = std::make_unique<CpuLoad>();
    }
    m_load->load_avg_1m = std::stof(cpu_load[0]);
    m_load->load_avg_3m = std::stof(cpu_load[1]);
    m_load->load_avg_15m = std::stof(cpu_load[2]);

    auto cpu_load_msg = monitor_info->mutable_cpu_load();
    cpu_load_msg->set_load_avg_1m(m_load->load_avg_1m);
    cpu_load_msg->set_load_avg_3m(m_load->load_avg_3m);
    cpu_load_msg->set_load_avg_15m(m_load->load_avg_15m);
}

void CpuLoadMonitor::Stop()
{
    m_load.reset();
}

} // namespace monitor