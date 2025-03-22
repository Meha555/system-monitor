#pragma once
#include <QAbstractTableModel>
#include <QObject>

#include "monitor_info.pb.h"

namespace models
{

class MonitorModelBase : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MonitorModelBase(QObject *parent = nullptr);
    virtual ~MonitorModelBase() = default;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    virtual void updateMonitorInfo(const monitor::proto::MonitorInfo &monito_info) = 0;

protected:
    QStringList m_header;
    QVector<QVector<QVariant>> m_monitor_data;
};

} // namespace monitor