#include "cpu_softirq_monitor.h"
#include "utils.h"

#include <glog/logging.h>

#include "monitor_info.pb.h"

namespace monitor
{
void CpuSoftIrqMonitor::UpdateOnce(monitor::proto::MonitorInfo *monitor_info)
{
    std::vector<std::vector<std::string>> cpu_softirqs;
    if (!Utils::ReadLines(kSoftIrqFile, cpu_softirqs)) {
        LOG(ERROR) << "Read " << kSoftIrqFile << " failed";
        return;
    }
    // 第一行是CPU信息
    for (int i = 0; i < cpu_softirqs[0].size() - 1; i++) {
        auto info = std::make_shared<struct SoftIrq>();
        info->name = cpu_softirqs[0][i];
        info->hi = std::stoll(cpu_softirqs[1][i + 1]);
        info->timer = std::stoll(cpu_softirqs[2][i + 1]);
        info->net_tx = std::stoll(cpu_softirqs[3][i + 1]);
        info->net_rx = std::stoll(cpu_softirqs[4][i + 1]);
        info->block = std::stoll(cpu_softirqs[5][i + 1]);
        info->irq_poll = std::stoll(cpu_softirqs[6][i + 1]);
        info->tasklet = std::stoll(cpu_softirqs[7][i + 1]);
        info->sched = std::stoll(cpu_softirqs[8][i + 1]);
        info->hrtimer = std::stoll(cpu_softirqs[9][i + 1]);
        info->rcu = std::stoll(cpu_softirqs[10][i + 1]);
        info->timepoint = std::chrono::steady_clock::now();
        // 需要统计变化，所以需要检查之前有没有数据
        auto iter = m_cpu_softirqs_map.find(info->name);
        if (iter != m_cpu_softirqs_map.end()) {
            auto old = (*iter).second;
            const auto period = Utils::SecondPassed(info->timepoint, old->timepoint);
            auto softirq_msg = monitor_info->add_soft_irq();
            softirq_msg->set_cpu(info->name);
            softirq_msg->set_hi_avg((info->hi - old->hi) / period);
            softirq_msg->set_timer_avg((info->timer - old->timer) / period);
            softirq_msg->set_net_tx_avg((info->net_tx - old->net_tx) / period);
            softirq_msg->set_net_rx_avg((info->net_rx - old->net_rx) / period);
            softirq_msg->set_block_avg((info->block - old->block) / period);
            softirq_msg->set_irq_poll_avg((info->irq_poll - old->irq_poll) / period);
            softirq_msg->set_tasklet_avg((info->tasklet - old->tasklet) / period);
            softirq_msg->set_sched_avg((info->sched - old->sched) / period);
            softirq_msg->set_hrtimer_avg((info->hrtimer - old->hrtimer) / period);
            softirq_msg->set_rcu_avg((info->rcu - old->rcu) / period);
        }
        m_cpu_softirqs_map[info->name] = info;
    }
    return;
}

void CpuSoftIrqMonitor::Stop()
{
    m_cpu_softirqs_map.clear();
}

} // namespace monitor

/*

                    CPU0       CPU1       CPU2       CPU3       CPU4       CPU5       CPU6       CPU7       CPU8       CPU9       CPU10      CPU11      CPU12      CPU13      CPU14      CPU15
          HI:    3993719         33         30         45         27         43         11     636369          0          0          0          0          0          0          0          0
       TIMER:    5775332    2793329    2624630    2571548    2808026    2668458    2571346    2556004          0          0          0          0          0          0          0          0
      NET_TX:        203         84         74         96         36         49         42         47          0          0          0          0          0          0          0          0
      NET_RX:    3745715     453583     224031     232532     222398     242588     243527     229344          0          0          0          0          0          0          0          0
       BLOCK:    1846162     210717       2034         98     511434     500593     506530     480941          0          0          0          0          0          0          0          0
    IRQ_POLL:        101          0          1          5          6         15          6          6          0          0          0          0          0          0          0          0
     TASKLET:     414589       5362        701        706        418        404        346      26112          0          0          0          0          0          0          0          0
       SCHED:   28658968   24844401   23272004   22493865   22943818   22363493   21961906   22309433          0          0          0          0          0          0          0          0
     HRTIMER:      35345        286        274        313        115        726        153        177          0          0          0          0          0          0          0          0
         RCU:   20941934   20382121   20305135   20284659   20225275   20154764   20060785   20528003          0          0          0          0          0          0          0          0

*/