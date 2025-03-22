#include "cpu_softirq_model.h"
#include "models/monitor_model.h"
#include <QDebug>

namespace models
{
CpuSoftIrqModel::CpuSoftIrqModel(QObject *parent)
    : MonitorModelBase(parent)
{
    m_header << tr("cpu")
             << tr("hi")
             << tr("timer")
             << tr("net_tx")
             << tr("net_rx")
             << tr("block")
             << tr("irq_poll")
             << tr("tasklet")
             << tr("sched")
             << tr("hrtimer")
             << tr("rcu");
}

int CpuSoftIrqModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

void CpuSoftIrqModel::updateMonitorInfo(const monitor::proto::MonitorInfo &monito_info)
{
    beginResetModel();
    m_monitor_data.clear();

    for (int i = 0; i < monito_info.soft_irq_size(); i++) {
        m_monitor_data.push_back(collect(monito_info.soft_irq(i)));
    }

    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();
}

QVector<QVariant> CpuSoftIrqModel::collect(const monitor::proto::SoftIrq &soft_irq)
{
    QVector<QVariant> soft_irq_list;
    for (int item = SoftIrqInfoItem::CPU_NAME; item < COLUMN_COUNT; item++) {
        switch (item) {
        case SoftIrqInfoItem::CPU_NAME:
            soft_irq_list.push_back(QVariant(QString::fromStdString(soft_irq.cpu())));
            break;
        case SoftIrqInfoItem::HI:
            soft_irq_list.push_back(QVariant(soft_irq.hi_avg()));
            break;
        case SoftIrqInfoItem::TIMER:
            soft_irq_list.push_back(QVariant(soft_irq.timer_avg()));
            break;
        case SoftIrqInfoItem::NET_TX:
            soft_irq_list.push_back(QVariant(soft_irq.net_tx_avg()));
            break;
        case SoftIrqInfoItem::NET_RX:
            soft_irq_list.push_back(QVariant(soft_irq.net_rx_avg()));
            break;
        case SoftIrqInfoItem::BLOCK:
            soft_irq_list.push_back(QVariant(soft_irq.block_avg()));
            break;
        case SoftIrqInfoItem::IRQ_POLL:
            soft_irq_list.push_back(QVariant(soft_irq.irq_poll_avg()));
            break;
        case SoftIrqInfoItem::TASKLET:
            soft_irq_list.push_back(QVariant(soft_irq.tasklet_avg()));
            break;
        case SoftIrqInfoItem::SCHED:
            soft_irq_list.push_back(QVariant(soft_irq.sched_avg()));
            break;
        case SoftIrqInfoItem::HRTIMER:
            soft_irq_list.push_back(QVariant(soft_irq.hrtimer_avg()));
            break;
        case SoftIrqInfoItem::RCU:
            soft_irq_list.push_back(QVariant(soft_irq.rcu_avg()));
            break;
        default:
            qWarning() << "unknown SoftIrqInfoItem";
            break;
        }
    }
    return soft_irq_list;
}
} // namespace monitor
