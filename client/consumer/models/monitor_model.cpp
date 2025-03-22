#include "monitor_model.h"

#include <QColor>
#include <QFont>
#include <qnamespace.h>

namespace models
{
MonitorModelBase::MonitorModelBase(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int MonitorModelBase::rowCount(const QModelIndex &parent) const
{
    return m_monitor_data.size();
}

QVariant MonitorModelBase::headerData(int section, Qt::Orientation orientation,
                                  int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        return m_header[section];
    }

    if (role == Qt::FontRole) {
        return QVariant::fromValue(QFont("Microsoft YaHei", 10, QFont::Bold));
    }

    if (role == Qt::BackgroundRole) {
        return QVariant::fromValue(QColor(Qt::lightGray));
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant MonitorModelBase::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        if (index.row() < m_monitor_data.size() && index.column() < columnCount(index.parent()))
            return m_monitor_data[index.row()][index.column()];
    }

    if (role == Qt::TextAlignmentRole) {
        return QVariant(Qt::AlignLeft | Qt::AlignVCenter);
    }

    if (role == Qt::ForegroundRole) {
        return QVariant::fromValue(QColor(Qt::black));
    }

    if (role == Qt::BackgroundRole) {
        return QVariant::fromValue(QColor(Qt::white));
    }

    return QVariant();
}

} // namespace monitor