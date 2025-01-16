#include "tablebox.h"
#include <QAbstractTableModel>
#include <QHeaderView>
#include <QLabel>
#include <QSortFilterProxyModel>
#include <QTableView>
#include <QVBoxLayout>

namespace components
{

TableBox::TableBox(bool enAbleSorting, QWidget *parent)
    : TableBox(QString(), nullptr, enAbleSorting, parent)
{
}

TableBox::TableBox(const QString &title, QAbstractTableModel *tableModel, bool enAbleSorting, QWidget *parent)
    : QWidget(parent)
    , m_label(new QLabel(title, this))
    , m_tableView(new QTableView(this))
    , m_tableModel(tableModel)
{
    m_label->setAlignment(Qt::AlignCenter);
    m_label->setFont(QFont("Consolas", 10, 40));
    m_tableView->resizeColumnsToContents();
    m_tableView->resizeRowsToContents();
    m_tableView->setAlternatingRowColors(true);
    m_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tableView->verticalHeader()->setHidden(true);

    if (enAbleSorting) {
        m_proxyModel = new QSortFilterProxyModel(this);
        m_proxyModel->setSourceModel(tableModel);
        m_proxyModel->setDynamicSortFilter(true);
        m_tableView->setModel(m_proxyModel);
        m_tableView->setSortingEnabled(true);
    } else {
        m_proxyModel = nullptr;
        m_tableView->setModel(tableModel);
    }

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_label, 1);
    layout->addWidget(m_tableView, 6);
    setLayout(layout);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_tableView->setSizePolicy(sizePolicy);
    setSizePolicy(sizePolicy);
}

void TableBox::setItemDelegate(QAbstractItemDelegate *delegate)
{
    m_tableView->setItemDelegate(delegate);
}

void TableBox::sortByColumn(int column)
{
    if (m_proxyModel) {
        m_proxyModel->sort(column, Qt::AscendingOrder);
    }
}

void TableBox::display()
{
    m_tableView->show();
}

void TableBox::shutdown()
{
    m_tableView->hide();
}

}