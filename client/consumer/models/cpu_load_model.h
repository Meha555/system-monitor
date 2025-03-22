#pragma once

#include <QAbstractTableModel>

#include "monitor_model.h"

#include "monitor_info.pb.h"

namespace models
{

class CpuLoadModel : public MonitorModelBase
{
    Q_OBJECT

public:
    explicit CpuLoadModel(QObject *parent = nullptr);

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    void updateMonitorInfo(const monitor::proto::MonitorInfo &monitor_info) override;

signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles);

private:
    QVector<QVariant> collect(const monitor::proto::CpuLoad &cpu_load);

    enum CpuLoadItem : int { CPU_AVG_1m = 0,
                             CPU_AVG_3m,
                             CPU_AVG_15m,
                             COLUMN_COUNT };
};

} // namespace monitor