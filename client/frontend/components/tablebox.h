#ifndef TABLEBOX_H
#define TABLEBOX_H

#include <QWidget>

class QLabel;
class QTableView;
class QAbstractTableModel;
class QSortFilterProxyModel;
class QAbstractItemDelegate;

namespace components
{
class TableBox : public QWidget
{
    Q_OBJECT
public:
    explicit TableBox(bool enAbleSorting = false, QWidget *parent = nullptr);
    explicit TableBox(const QString &title, QAbstractTableModel *tableModel, bool enAbleSorting = false, QWidget *parent = nullptr);
    virtual ~TableBox() = default;

    void setItemDelegate(QAbstractItemDelegate *delegate);

    void sortByColumn(int column);
    QAbstractTableModel *model() const
    {
        return m_tableModel;
    }

public slots:
    void display();
    void shutdown();

protected:
    QLabel *m_label;
    QTableView *m_tableView;
    QAbstractTableModel *m_tableModel;
    QSortFilterProxyModel *m_proxyModel;
};
}
#endif // TABLEBOX_H
