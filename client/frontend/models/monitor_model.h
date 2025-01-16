#pragma once
#include <QAbstractTableModel>
#include <QObject>

#include "monitor_info.pb.h"

namespace models
{

class MonitorModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit MonitorModel(QObject *parent = nullptr);
    virtual ~MonitorModel() = default;

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

    virtual void updateMonitorInfo(const monitor::proto::MonitorInfo &monito_info) = 0;

protected:
    QStringList m_header;
    QVector<QVector<QVariant>> m_monitor_data;
};

} // namespace monitor