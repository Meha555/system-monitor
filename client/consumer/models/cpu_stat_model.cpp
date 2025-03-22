#include "cpu_stat_model.h"
#include <QDebug>

namespace models
{
CpuStatModel::CpuStatModel(QObject *parent)
    : MonitorModelBase(parent)
{
    m_header << tr("name")
             << tr("cpu_percent")
             << tr("user")
             << tr("system");
}

int CpuStatModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

void CpuStatModel::updateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    beginResetModel();
    m_monitor_data.clear();

    for (int i = 0; i < monitor_info.cpu_stat_size(); i++) {
        m_monitor_data.push_back(collect(monitor_info.cpu_stat(i)));
    }
    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();
}

QVector<QVariant> CpuStatModel::collect(const monitor::proto::CpuStat &cpu_stat)
{
    QVector<QVariant> cpu_stat_list;
    for (int item = CpuStatItem::CPU_NAME; item < COLUMN_COUNT; item++) {
        switch (item) {
        case CpuStatItem::CPU_NAME:
            cpu_stat_list.push_back(QString::fromStdString(cpu_stat.name()));
            break;
        case CpuStatItem::CPU_PERCENT:
            cpu_stat_list.push_back(QVariant(cpu_stat.cpu_percent()));
            break;
        case CpuStatItem::CPU_USER_PERCENT:
            cpu_stat_list.push_back(QVariant(cpu_stat.usr_percent()));
            break;
        case CpuStatItem::CPU_SYSTEM_PERCENT:
            cpu_stat_list.push_back(QVariant(cpu_stat.system_percent()));
            break;
        default:
            qWarning() << "unknown CpuStatItem";
            break;
        }
    }
    return cpu_stat_list;
}
} // namespace monitor
