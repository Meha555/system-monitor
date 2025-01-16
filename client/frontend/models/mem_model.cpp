#include "mem_model.h"
#include <QDebug>

namespace models
{
MemModel::MemModel(QObject *parent)
    : MonitorModel(parent)
{
    m_header << tr("used_percent");
    m_header << tr("total");
    m_header << tr("free");
    m_header << tr("avail");
    m_header << tr("buffers");
    m_header << tr("cached");
    m_header << tr("swap_cached");
    m_header << tr("active");
    m_header << tr("in_active");
    m_header << tr("active_anon");
    m_header << tr("inactive_anon");
    m_header << tr("active_file");
    m_header << tr("inactive_file");
    m_header << tr("dirty");
    m_header << tr("writeback");
    m_header << tr("anon_pages");
    m_header << tr("mapped");
    m_header << tr("kReclaimable");
    m_header << tr("sReclaimable");
    m_header << tr("sUnreclaim");
}

int MemModel::rowCount(const QModelIndex &parent) const
{
    return m_monitor_data.size();
}

int MemModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

QVariant MemModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_header[section];
    }

    return MonitorModel::headerData(section, orientation, role);
}

QVariant MemModel::data(const QModelIndex &index, int role) const
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

void MemModel::updateMonitorInfo(
    const monitor::proto::MonitorInfo &monitor_info)
{
    beginResetModel();
    m_monitor_data.clear();

    m_monitor_data.push_back(insert(monitor_info.mem_info()));

    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();
}

QVector<QVariant> MemModel::insert(
    const monitor::proto::MemInfo &mem_info)
{
    QVector<QVariant> mem_info_list;
    for (int i = MemInfoItem::USED_PERCENT; i < COLUMN_COUNT; i++) {
        switch (i) {
        case MemInfoItem::USED_PERCENT:
            mem_info_list.push_back(QVariant(mem_info.used_percent()));
            break;
        case MemInfoItem::TOTAL:
            mem_info_list.push_back(QVariant(mem_info.total()));
            break;
        case MemInfoItem::FREE:
            mem_info_list.push_back(QVariant(mem_info.free()));
            break;
        case MemInfoItem::AVAIL:
            mem_info_list.push_back(QVariant(mem_info.avail()));
            break;
        case MemInfoItem::BUFFERS:
            mem_info_list.push_back(QVariant(mem_info.buffers()));
            break;
        case MemInfoItem::CACHED:
            mem_info_list.push_back(QVariant(mem_info.cached()));
            break;
        case MemInfoItem::SWAP_CACHED:
            mem_info_list.push_back(QVariant(mem_info.swap_cached()));
            break;
        case MemInfoItem::ACTIVE:
            mem_info_list.push_back(QVariant(mem_info.active()));
            break;
        case MemInfoItem::INACTIVE:
            mem_info_list.push_back(QVariant(mem_info.inactive()));
            break;
        case MemInfoItem::ACTIVE_ANON:
            mem_info_list.push_back(QVariant(mem_info.active_anon()));
            break;
        case MemInfoItem::INACTIVE_ANON:
            mem_info_list.push_back(QVariant(mem_info.inactive_anon()));
            break;
        case MemInfoItem::DIRTY:
            mem_info_list.push_back(QVariant(mem_info.dirty()));
            break;
        case MemInfoItem::WRITEBACK:
            mem_info_list.push_back(QVariant(mem_info.writeback()));
            break;
        case MemInfoItem::ANON_PAGES:
            mem_info_list.push_back(QVariant(mem_info.anon_pages()));
            break;
        case MemInfoItem::MAPPED:
            mem_info_list.push_back(QVariant(mem_info.mapped()));
            break;
        case MemInfoItem::KRECLAIMABLE:
            mem_info_list.push_back(QVariant(mem_info.kreclaimable()));
            break;
        case MemInfoItem::SRECLAIMABLE:
            mem_info_list.push_back(QVariant(mem_info.sreclaimable()));
            break;
        case MemInfoItem::SUNRECLAIM:
            mem_info_list.push_back(QVariant(mem_info.sunreclaim()));
            break;
        default:
            qWarning() << "unknown MemInfoItem";
            break;
        }
    }
    return mem_info_list;
}
} // namespace monitor
