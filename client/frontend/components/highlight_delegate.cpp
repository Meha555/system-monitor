#include "highlight_delegate.h"
#include <QDebug>

namespace components
{

HighlightDelegate::HighlightDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void HighlightDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    QVariant value = index.model()->data(index, Qt::DisplayRole);
    QStyleOptionViewItem opt = option;
    if (value.canConvert<double>()) {
        double num = value.toDouble();
        if (num > 70) {
            opt.palette.setColor(QPalette::Text, Qt::red);
        } else if (num > 50) {
            opt.palette.setColor(QPalette::Text, Qt::yellow);
        } else if (num > 20) {
            opt.palette.setColor(QPalette::Text, Qt::green);
        }
    }
    QStyledItemDelegate::paint(painter, opt, index);
}

}