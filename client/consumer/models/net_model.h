#pragma once

#include <QAbstractTableModel>

#include "monitor_model.h"

#include "monitor_info.pb.h"

namespace models
{

class NetModel : public MonitorModel
{
    Q_OBJECT

public:
    explicit NetModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

    void updateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info) override;

signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles);

private:
    QVector<QVariant> insert(const monitor::proto::NetInfo &net_info);

    enum NetModelInfo {
        NAME = 0,
        SEND_RATE,
        RCV_RATE,
        SEND_PACKETS_RATE,
        RCV_PACKETS_RATE,
        COLUMN_MAX
    };
};

} // namespace monitor