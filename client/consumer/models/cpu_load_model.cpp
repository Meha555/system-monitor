#include "cpu_load_model.h"
#include <QDebug>

namespace models
{
CpuLoadModel::CpuLoadModel(QObject *parent)
    : MonitorModelBase(parent)
{
    m_header << tr("load_1m")
             << tr("load_3m")
             << tr("load_15m");
}

int CpuLoadModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

void CpuLoadModel::updateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    beginResetModel();
    m_monitor_data.clear();

    m_monitor_data.push_back(collect(monitor_info.cpu_load()));

    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_COUNT);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();
}

QVector<QVariant> CpuLoadModel::collect(const monitor::proto::CpuLoad &cpu_load)
{
    QVector<QVariant> cpu_load_list;
    for (int item = CpuLoadItem::CPU_AVG_1m; item < COLUMN_COUNT; item++) {
        switch (item) {
        case CpuLoadItem::CPU_AVG_1m:
            cpu_load_list.push_back(QVariant(cpu_load.load_avg_1m()));
            break;
        case CpuLoadItem::CPU_AVG_3m:
            cpu_load_list.push_back(QVariant(cpu_load.load_avg_3m()));
            break;
        case CpuLoadItem::CPU_AVG_15m:
            cpu_load_list.push_back(QVariant(cpu_load.load_avg_15m()));
            break;
        default:
            qWarning() << "unknown CpuLoadItem";
            break;
        }
    }
    return cpu_load_list;
}
} // namespace monitor
