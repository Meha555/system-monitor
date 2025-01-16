#pragma once

#include <QAbstractTableModel>

#include "monitor_model.h"

#include "monitor_info.pb.h"

namespace models
{

class MemModel : public MonitorModel
{
    Q_OBJECT

public:
    explicit MemModel(QObject *parent = nullptr);

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
    QVector<QVariant> insert(const monitor::proto::MemInfo &mem_info);

    enum MemInfoItem {
        USED_PERCENT = 0,
        TOTAL,
        FREE,
        AVAIL,
        BUFFERS,
        CACHED,
        SWAP_CACHED,
        ACTIVE,
        INACTIVE,
        ACTIVE_ANON,
        INACTIVE_ANON,
        DIRTY,
        WRITEBACK,
        ANON_PAGES,
        MAPPED,
        KRECLAIMABLE,
        SRECLAIMABLE,
        SUNRECLAIM,
        COLUMN_COUNT
    };
};

} // namespace monitor