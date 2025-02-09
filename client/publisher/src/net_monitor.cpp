#include "net_monitor.h"
#include "utils.h"

#include <glog/logging.h>

namespace monitor
{
void NetMonitor::UpdateOnce(monitor::proto::MonitorInfo *monitor_info)
{
    std::vector<std::vector<std::string>> net_datas;
    if (!Utils::ReadLines(kNetFile, net_datas)) {
        LOG(ERROR) << "Read file " << kNetFile << " failed";
        return;
    }
    // 遍历每个网卡
    for (const auto &net_data : net_datas) {
        std::string name = net_data[0];
        if (name.back() == ':') {
            auto net_info = std::make_unique<NetInfo>();
            name.pop_back();
            net_info->name = name;
            net_info->rcv_bytes = std::stoll(net_data[1]);
            net_info->rcv_packets = std::stoll(net_data[2]);
            net_info->rcv_err = std::stoll(net_data[3]);
            net_info->rcv_drop = std::stoll(net_data[4]);
            net_info->snd_bytes = std::stoll(net_data[9]);
            net_info->snd_packets = std::stoll(net_data[10]);
            net_info->snd_err = std::stoll(net_data[11]);
            net_info->snd_drop = std::stoll(net_data[12]);
            net_info->timepoint = std::chrono::steady_clock::now();

            auto iter = m_net_info_map.find(name);
            if (iter != m_net_info_map.end()) {
                auto old = std::move(iter->second);

                const auto period = Utils::SecondPassed(net_info->timepoint, old->timepoint);
                auto net_info_msg = monitor_info->add_net_info();
                net_info_msg->set_name(net_info->name);
                net_info_msg->set_send_rate((net_info->snd_bytes - old->snd_bytes) / 1024.0 / period);
                net_info_msg->set_rcv_rate((net_info->rcv_bytes - old->rcv_bytes) / 1024.0 / period);
                net_info_msg->set_send_packets_rate((net_info->snd_packets - old->snd_packets) / period);
                net_info_msg->set_rcv_packets_rate((net_info->rcv_packets - old->rcv_packets) / period);
            }
            m_net_info_map[name] = std::move(net_info);
        }
    }
}

void NetMonitor::Stop()
{
    m_net_info_map.clear();
}

} // namespace monitor

/*

Inter-|   Receive                                                |  Transmit
 face |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
    lo: 443307934 2370277    0    0    0     0          0         0 443307934 2370277    0    0    0     0       0          0
enp1s0:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
wlp2s0: 7258398439 6173688    0   11    0     0          0         0 723087636 2597118    0    0    0     0       0          0
docker0: 25529559  468816    0    0    0     0          0         0 79194699  369966    0    0    0     0       0          0

bytes: 接口发送或接收的数据的总字节数。

packets: 接口发送或接收的数据包总数。

errs: 由设备驱动程序检测到的发送或接收错误的总数。

drop: 设备驱动程序丢弃的数据包总数。

fifo: FIFO缓冲区错误的数量。

frame: 分组帧错误的数量。

colls: 接口上检测到的冲突数。

compressed: 设备驱动程序发送或接收的压缩数据包数。

carrier: 由设备驱动程序检测到的载波损耗的数量。

multicast: 设备驱动程序发送或接收的多播帧数。

*/