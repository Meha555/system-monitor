#include "mem_model.h"
#include <QDebug>

namespace models
{
MemModel::MemModel(QObject *parent)
    : MonitorModelBase(parent)
{
    m_header << tr("used_percent")
             << tr("total")
             << tr("free")
             << tr("avail")
             << tr("buffers")
             << tr("cached")
             << tr("swap_cached")
             << tr("active")
             << tr("in_active")
             << tr("active_anon")
             << tr("inactive_anon")
             << tr("active_file")
             << tr("inactive_file")
             << tr("dirty")
             << tr("writeback")
             << tr("anon_pages")
             << tr("mapped")
             << tr("kReclaimable")
             << tr("sReclaimable")
             << tr("sUnreclaim");
}

int MemModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_COUNT;
}

void MemModel::updateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    beginResetModel();
    m_monitor_data.clear();

    m_monitor_data.push_back(collect(monitor_info.mem_info()));

    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();
}

QVector<QVariant> MemModel::collect(const monitor::proto::MemInfo &mem_info)
{
    QVector<QVariant> mem_info_list;
    for (int item = MemInfoItem::USED_PERCENT; item < COLUMN_COUNT; item++) {
        switch (item) {
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
