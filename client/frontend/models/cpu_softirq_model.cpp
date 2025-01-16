#include "cpu_softirq_model.h"
#include <QDebug>

namespace models
{
CpuSoftIrqModel::CpuSoftIrqModel(QObject *parent)
    : MonitorModel(parent)
{
    m_header << tr("cpu");
    m_header << tr("hi");
    m_header << tr("timer");
    m_header << tr("net_tx");
    m_header << tr("net_rx");
    m_header << tr("block");
    m_header << tr("irq_poll");
    m_header << tr("tasklet");
    m_header << tr("sched");
    m_header << tr("hrtimer");
    m_header << tr("rcu");
}

int CpuSoftIrqModel::rowCount(const QModelIndex &parent) const
{
    return m_monitor_data.size();
}

int CpuSoftIrqModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

QVariant CpuSoftIrqModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_header[section];
    }

    return MonitorModel::headerData(section, orientation, role);
}

QVariant CpuSoftIrqModel::data(const QModelIndex &index, int role) const
{
    if (index.column() < 0 || index.column() >= COLUMN_COUNT) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        if (index.row() < m_monitor_data.size() && index.column() < COLUMN_COUNT)
            return m_monitor_data[index.row()][index.column()];
    }
    return QVariant();
}

void CpuSoftIrqModel::updateMonitorInfo(const monitor::proto::MonitorInfo &monito_info)
{
    beginResetModel();
    m_monitor_data.clear();

    for (int i = 0; i < monito_info.soft_irq_size(); i++) {
        m_monitor_data.push_back(insert(monito_info.soft_irq(i)));
    }

    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();
    return;
}

QVector<QVariant> CpuSoftIrqModel::insert(const monitor::proto::SoftIrq &soft_irq)
{
    QVector<QVariant> soft_irq_list;
    for (int i = SoftIrqInfoItem::CPU_NAME; i < COLUMN_COUNT; i++) {
        switch (i) {
        case SoftIrqInfoItem::CPU_NAME:
            soft_irq_list.push_back(
                QVariant(QString::fromStdString(soft_irq.cpu())));
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
