#include "cpu_load_model.h"
#include <QDebug>

namespace models
{
CpuLoadModel::CpuLoadModel(QObject *parent)
    : MonitorModel(parent)
{
    m_header << tr("load_1m");
    m_header << tr("load_3m");
    m_header << tr("load_15m");
}

int CpuLoadModel::rowCount(const QModelIndex &parent) const
{
    return m_monitor_data.size();
}

int CpuLoadModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

QVariant CpuLoadModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_header[section];
    }

    return MonitorModel::headerData(section, orientation, role);
}

QVariant CpuLoadModel::data(const QModelIndex &index, int role) const
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

void CpuLoadModel::updateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    beginResetModel();
    m_monitor_data.clear();

    m_monitor_data.push_back(insert(monitor_info.cpu_load()));

    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_COUNT);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();
}

QVector<QVariant> CpuLoadModel::insert(const monitor::proto::CpuLoad &cpu_load)
{
    QVector<QVariant> cpu_load_list;
    for (int i = CpuLoadItem::CPU_AVG_1m; i < COLUMN_COUNT; i++) {
        switch (i) {
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
