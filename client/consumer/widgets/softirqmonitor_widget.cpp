#include "softirqmonitor_widget.h"
#include "components/highlight_delegate.h"
#include "models/cpu_softirq_model.h"
#include "widgets/monitor_widget.h"
#include <QGridLayout>

namespace widgets
{

SoftIrqMonitorWidget::SoftIrqMonitorWidget(MonitorWidget *parent)
    : MonitorWidget(parent)
    , m_softirq_box(new components::TableBox(tr("Monitor Soft Irq"), new models::CpuSoftIrqModel(this), false, this))
{
}

void SoftIrqMonitorWidget::init()
{
    m_softirq_box->setItemDelegate(new components::HighlightDelegate(this));
    connect(this, &SoftIrqMonitorWidget::inited, m_softirq_box, &components::TableBox::display);
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(m_softirq_box);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    emit inited();
}

void SoftIrqMonitorWidget::updateInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    qobject_cast<models::CpuSoftIrqModel *>(m_softirq_box->model())->updateMonitorInfo(monitor_info);
}

}