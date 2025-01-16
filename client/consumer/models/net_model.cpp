#include "net_model.h"
#include <QDebug>

namespace models
{

NetModel::NetModel(QObject *parent)
    : MonitorModel(parent)
{
    m_header << tr("name");
    m_header << tr("send_rate");
    m_header << tr("rcv_rate");
    m_header << tr("send_packets_rate");
    m_header << tr("rcv_packets_rate");
}

int NetModel::rowCount(const QModelIndex &parent) const
{
    return m_monitor_data.size();
}

int NetModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_MAX;
}

QVariant NetModel::headerData(int section, Qt::Orientation orientation,
                              int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_header[section];
    }

    return MonitorModel::headerData(section, orientation, role);
}

QVariant NetModel::data(const QModelIndex &index, int role) const
{
    if (index.column() < 0 || index.column() >= COLUMN_MAX) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        if (index.row() < m_monitor_data.size() && index.column() < COLUMN_MAX)
            return m_monitor_data[index.row()][index.column()];
    }
    return QVariant();
}

void NetModel::updateMonitorInfo(
    const monitor::proto::MonitorInfo &monitor_info)
{
    beginResetModel();
    m_monitor_data.clear();

    for (int i = 0; i < monitor_info.net_info_size(); i++) {
        m_monitor_data.push_back(insert(monitor_info.net_info(i)));
    }

    // QModelIndex leftTop = createIndex(0, 0);
    // QModelIndex rightBottom = createIndex(monitor_data_.size(), COLUMN_MAX);
    // emit dataChanged(leftTop, rightBottom, {});

    endResetModel();
}

QVector<QVariant> NetModel::insert(const monitor::proto::NetInfo &net_info)
{
    QVector<QVariant> net_info_list;
    for (int i = NetModelInfo::NAME; i < COLUMN_MAX; i++) {
        switch (i) {
        case NetModelInfo::NAME:
            net_info_list.push_back(
                QString::fromStdString(net_info.name()));
            break;
        case NetModelInfo::SEND_RATE:
            net_info_list.push_back(QVariant(net_info.send_rate()));
            break;
        case NetModelInfo::RCV_RATE:
            net_info_list.push_back(QVariant(net_info.rcv_rate()));
            break;
        case NetModelInfo::SEND_PACKETS_RATE:
            net_info_list.push_back(QVariant(net_info.send_packets_rate()));
            break;
        case NetModelInfo::RCV_PACKETS_RATE:
            net_info_list.push_back(QVariant(net_info.rcv_packets_rate()));
            break;
        default:
            qWarning() << "unknown NetModelInfo";
            break;
        }
    }
    return net_info_list;
}
} // namespace monitor
