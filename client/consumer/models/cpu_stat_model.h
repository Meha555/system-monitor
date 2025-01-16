#pragma once

#include <QAbstractTableModel>

#include "monitor_model.h"

#include "monitor_info.pb.h"

namespace models
{

class CpuStatModel : public MonitorModel
{
    Q_OBJECT

public:
    explicit CpuStatModel(QObject *parent = nullptr);

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
    QVector<QVariant> insert(const monitor::proto::CpuStat &cpu_stat);

    enum CpuStatItem {
        CPU_NAME = 0,
        CPU_PERCENT,
        CPU_USER_PERCENT,
        CPU_SYSTEM_PERCENT,
        COLUMN_COUNT
    };
};

} // namespace monitor