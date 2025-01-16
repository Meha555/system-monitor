#include "softirqmonitor_factory.h"
#include "widgets/softirqmonitor_widget.h"

namespace factories
{

widgets::MonitorWidget *SoftIrqMonitorFactory::createMonitorWidget()
{
    widgets::MonitorWidget *widget = new widgets::SoftIrqMonitorWidget();
    widget->init();
    return widget;
}

}