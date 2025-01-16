#pragma once

#include <QStyledItemDelegate>

namespace components
{

class HighlightDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit HighlightDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
};

}