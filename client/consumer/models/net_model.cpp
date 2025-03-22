#include "net_model.h"
#include <QDebug>

namespace models
{

NetModel::NetModel(QObject *parent)
    : MonitorModelBase(parent)
{
    m_header << tr("name")
             << tr("send_rate")
             << tr("rcv_rate")
             << tr("send_packets_rate")
             << tr("rcv_packets_rate");
}

int NetModel::columnCount(const QModelIndex &parent) const
{
    return COLUMN_MAX;
}

void NetModel::updateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info)
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
    for (int item = NetModelInfo::NAME; item < COLUMN_MAX; item++) {
        switch (item) {
        case NetModelInfo::NAME:
            net_info_list.push_back(QString::fromStdString(net_info.name()));
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
