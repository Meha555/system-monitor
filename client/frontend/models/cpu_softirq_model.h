#pragma once

#include <QAbstractTableModel>

#include "monitor_model.h"

#include "monitor_info.pb.h"

namespace models
{

class CpuSoftIrqModel : public MonitorModel
{
    Q_OBJECT

public:
    explicit CpuSoftIrqModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const override;

    void updateMonitorInfo(const monitor::proto::MonitorInfo &monito_info) override;

signals:
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight,
                     const QVector<int> &roles);

private:
    QVector<QVariant> insert(const monitor::proto::SoftIrq &soft_irq);

    enum SoftIrqInfoItem {
        CPU_NAME = 0,
        HI,
        TIMER,
        NET_TX,
        NET_RX,
        BLOCK,
        IRQ_POLL,
        TASKLET,
        SCHED,
        HRTIMER,
        RCU,
        COLUMN_COUNT
    };
};

} // namespace monitor