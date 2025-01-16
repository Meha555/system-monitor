#include "cpu_stat_model.h"
#include <QDebug>

namespace models
{
CpuStatModel::CpuStatModel(QObject *parent)
    : MonitorModel(parent)
{
    m_header << tr("name");
    m_header << tr("cpu_percent");
    m_header << tr("user");
    m_header << tr("system");
}

int CpuStatModel::rowCount(const QModelIndex &parent) const
{
    return m_monitor_data.size();
}

int CpuStatModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

QVariant CpuStatModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_header[section];
    }

    return MonitorModel::headerData(section, orientation, role);
}

QVariant CpuStatModel::data(const QModelIndex &index, int role) const
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

void CpuStatModel::updateMonitorInfo(
    const monitor::proto::MonitorInfo &monitor_info)
{
    beginResetModel();
    m_monitor_data.clear();

    for (int i = 0; i < monitor_info.cpu_stat_size(); i++) {
        // std::cout <<monitor_info.cpu_stat(i).name()<<std::endl;
        m_monitor_data.push_back(insert(monitor_info.cpu_stat(i)));
    }
    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();

    return;
}

QVector<QVariant> CpuStatModel::insert(const monitor::proto::CpuStat &cpu_stat)
{
    QVector<QVariant> cpu_stat_list;
    for (int i = CpuStatItem::CPU_NAME; i < COLUMN_COUNT; i++) {
        switch (i) {
        case CpuStatItem::CPU_NAME:
            cpu_stat_list.push_back(
                QString::fromStdString(cpu_stat.name()));
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
