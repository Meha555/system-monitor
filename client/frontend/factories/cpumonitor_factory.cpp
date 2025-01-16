#include "cpumonitor_factory.h"
#include "widgets/cpumonitor_widget.h"

namespace factories
{

widgets::MonitorWidget *CpuMonitorFactory::createMonitorWidget()
{
    widgets::MonitorWidget *widget = new widgets::CpuMonitorWidget();
    widget->init();
    return widget;
}

}