#include "cpumonitor_widget.h"
#include "components/highlight_delegate.h"
#include "models/cpu_load_model.h"
#include "models/cpu_stat_model.h"
#include <QVBoxLayout>

namespace widgets
{

CpuMonitorWidget::CpuMonitorWidget(MonitorWidget *parent)
    : MonitorWidget(parent)
    , m_cpu_load_box(new components::TableBox(tr("Monitor CPU Load"), new models::CpuLoadModel(this), false, this))
    , m_cpu_stat_box(new components::TableBox(tr("Monitor CPU Stat"), new models::CpuStatModel(this), false, this))
{
}

void CpuMonitorWidget::init()
{
    m_cpu_load_box->setItemDelegate(new components::HighlightDelegate(this));
    m_cpu_stat_box->setItemDelegate(new components::HighlightDelegate(this));
    connect(this, &CpuMonitorWidget::inited, m_cpu_load_box, &components::TableBox::display);
    connect(this, &CpuMonitorWidget::inited, m_cpu_stat_box, &components::TableBox::display);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_cpu_load_box, 1);
    layout->addWidget(m_cpu_stat_box, 6);
    setLayout(layout);

    emit inited();
}

void CpuMonitorWidget::updateInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    qobject_cast<models::CpuLoadModel *>(m_cpu_load_box->model())->updateMonitorInfo(monitor_info);
    qobject_cast<models::CpuStatModel *>(m_cpu_stat_box->model())->updateMonitorInfo(monitor_info);
}

}