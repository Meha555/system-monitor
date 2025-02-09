#include "mem_monitor.h"
#include "utils.h"

#include <glog/logging.h>

namespace monitor
{

static constexpr float KBToGB = 1000 * 1000;

void MemMonitor::UpdateOnce(monitor::proto::MonitorInfo *monitor_info)
{
    std::vector<std::vector<std::string>> mem_datas;
    if (!Utils::ReadLines(kMemInfoFile, mem_datas)) {
        LOG(ERROR) << "Read file " << kMemInfoFile << " failed";
        return;
    }
    if (!m_mem_info) {
        m_mem_info = std::make_unique<MemInfo>();
    }
    for (const auto &mem_data : mem_datas) {
        if (mem_data[0] == "MemTotal:") {
            m_mem_info->total = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "MemFree:") {
            m_mem_info->free = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "MemAvailable:") {
            m_mem_info->avail = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Buffers:") {
            m_mem_info->buffers = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Cached:") {
            m_mem_info->cached = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "SwapCached:") {
            m_mem_info->swap_cached = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Active:") {
            m_mem_info->active = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Inactive:") {
            m_mem_info->in_active = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Active(anon):") {
            m_mem_info->active_anon = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Inactive(anon):") {
            m_mem_info->inactive_anon = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Active(file):") {
            m_mem_info->active_file = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Inactive(file):") {
            m_mem_info->inactive_file = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Dirty:") {
            m_mem_info->dirty = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Writeback:") {
            m_mem_info->writeback = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "AnonPages:") {
            m_mem_info->anon_pages = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "Mapped:") {
            m_mem_info->mapped = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "KReclaimable:") {
            m_mem_info->kReclaimable = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "SReclaimable:") {
            m_mem_info->sReclaimable = std::stoll(mem_data[1]);
        } else if (mem_data[0] == "SUnreclaim:") {
            m_mem_info->sUnreclaim = std::stoll(mem_data[1]);
        }
    }

    auto mem_info_msg = monitor_info->mutable_mem_info();

    mem_info_msg->set_used_percent((m_mem_info->total - m_mem_info->avail) * 1.0 / m_mem_info->total * 100.0);
    mem_info_msg->set_total(m_mem_info->total / KBToGB);
    mem_info_msg->set_free(m_mem_info->free / KBToGB);
    mem_info_msg->set_avail(m_mem_info->avail / KBToGB);
    mem_info_msg->set_buffers(m_mem_info->buffers / KBToGB);
    mem_info_msg->set_cached(m_mem_info->cached / KBToGB);
    mem_info_msg->set_swap_cached(m_mem_info->swap_cached / KBToGB);
    mem_info_msg->set_active(m_mem_info->active / KBToGB);
    mem_info_msg->set_inactive(m_mem_info->in_active / KBToGB);
    mem_info_msg->set_active_anon(m_mem_info->active_anon / KBToGB);
    mem_info_msg->set_inactive_anon(m_mem_info->inactive_anon / KBToGB);
    mem_info_msg->set_active_file(m_mem_info->active_file / KBToGB);
    mem_info_msg->set_inactive_file(m_mem_info->inactive_file / KBToGB);
    mem_info_msg->set_dirty(m_mem_info->dirty / KBToGB);
    mem_info_msg->set_writeback(m_mem_info->writeback / KBToGB);
    mem_info_msg->set_anon_pages(m_mem_info->anon_pages / KBToGB);
    mem_info_msg->set_mapped(m_mem_info->mapped / KBToGB);
    mem_info_msg->set_kreclaimable(m_mem_info->kReclaimable / KBToGB);
    mem_info_msg->set_sreclaimable(m_mem_info->sReclaimable / KBToGB);
    mem_info_msg->set_sunreclaim(m_mem_info->sUnreclaim / KBToGB);
}

void MemMonitor::Stop()
{
    m_mem_info.reset();
}

} // namespace monitor
