#include "cpu_stat_monitor.h"
#include "utils.h"

#include <glog/logging.h>

#include "monitor_info.pb.h"

namespace monitor
{
void CpuStatMonitor::UpdateOnce(monitor::proto::MonitorInfo *monitor_info)
{
    std::vector<std::vector<std::string>> cpu_stat_list;
    if (!Utils::ReadLines(kStatFile, cpu_stat_list)) {
        LOG(ERROR) << "Read " << kStatFile << " failed";
        return;
    }
    for (const auto &cpu_stat_line : cpu_stat_list) {
        if (cpu_stat_line[0].find("cpu") == std::string::npos) {
            break;
        }
        auto cpu_stat = std::make_shared<CpuStat>();
        cpu_stat->name = cpu_stat_line[0];
        cpu_stat->user = std::stof(cpu_stat_line[1]);
        cpu_stat->nice = std::stof(cpu_stat_line[2]);
        cpu_stat->system = std::stof(cpu_stat_line[3]);
        cpu_stat->idle = std::stof(cpu_stat_line[4]);
        cpu_stat->io_wait = std::stof(cpu_stat_line[5]);
        cpu_stat->irq = std::stof(cpu_stat_line[6]);
        cpu_stat->soft_irq = std::stof(cpu_stat_line[7]);
        cpu_stat->steal = std::stof(cpu_stat_line[8]);
        cpu_stat->guest = std::stof(cpu_stat_line[9]);
        cpu_stat->guest_nice = std::stof(cpu_stat_line[10]);

        auto it = m_cpu_stat_map.find(cpu_stat->name);
        if (it != m_cpu_stat_map.end()) {
            auto old = it->second;

            float new_cpu_total_time = cpu_stat->user + cpu_stat->system + cpu_stat->idle + cpu_stat->nice + cpu_stat->io_wait + cpu_stat->irq + cpu_stat->soft_irq + cpu_stat->steal;
            float old_cpu_total_time = old->user + old->system + old->idle + old->nice + old->io_wait + old->irq + old->soft_irq + old->steal;
            float new_cpu_busy_time = cpu_stat->user + cpu_stat->system + cpu_stat->nice + cpu_stat->irq + cpu_stat->soft_irq + cpu_stat->steal;
            float old_cpu_busy_time = old->user + old->system + old->nice + old->irq + old->soft_irq + old->steal;

            float cpu_percent = (new_cpu_busy_time - old_cpu_busy_time) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
            float cpu_user_percent = (cpu_stat->user - old->user) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
            float cpu_system_percent = (cpu_stat->system - old->system) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
            float cpu_nice_percent = (cpu_stat->nice - old->nice) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
            float cpu_idle_percent = (cpu_stat->idle - old->idle) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
            float cpu_io_wait_percent = (cpu_stat->io_wait - old->io_wait) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
            float cpu_irq_percent = (cpu_stat->irq - old->irq) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
            float cpu_soft_irq_percent = (cpu_stat->soft_irq - old->soft_irq) / (new_cpu_total_time - old_cpu_total_time) * 100.00;

            auto cpu_stat_msg = monitor_info->add_cpu_stat();
            cpu_stat_msg->set_name(cpu_stat->name);
            cpu_stat_msg->set_cpu_percent(cpu_percent);
            cpu_stat_msg->set_usr_percent(cpu_user_percent);
            cpu_stat_msg->set_system_percent(cpu_system_percent);
            cpu_stat_msg->set_nice_percent(cpu_nice_percent);
            cpu_stat_msg->set_idle_percent(cpu_idle_percent);
            cpu_stat_msg->set_io_wait_percent(cpu_io_wait_percent);
            cpu_stat_msg->set_irq_percent(cpu_irq_percent);
            cpu_stat_msg->set_soft_irq_percent(cpu_soft_irq_percent);
        }
        m_cpu_stat_map[cpu_stat->name] = cpu_stat;
    }
}

void CpuStatMonitor::Stop()
{
    m_cpu_stat_map.clear();
}

} // namespace monitor