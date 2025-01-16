#include "memmonitor_widget.h"
#include "components/highlight_delegate.h"
#include "models/mem_model.h"
#include <QGridLayout>

namespace widgets
{
MemMonitorWidget::MemMonitorWidget(MonitorWidget *parent)
    : MonitorWidget(parent)
    , m_mem_box(new components::TableBox(tr("Monitor Memory"), new models::MemModel(this), false, this))
{
}

void MemMonitorWidget::init()
{
    m_mem_box->setItemDelegate(new components::HighlightDelegate(this));
    connect(this, &MemMonitorWidget::inited, m_mem_box, &components::TableBox::display);
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(m_mem_box);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    emit inited();
}

void MemMonitorWidget::updateInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    qobject_cast<models::MemModel *>(m_mem_box->model())->updateMonitorInfo(monitor_info);
}

}