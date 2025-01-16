#include "memmonitor_factory.h"
#include "widgets/memmonitor_widget.h"

namespace factories
{

widgets::MonitorWidget *MemMonitorFactory::createMonitorWidget()
{
    widgets::MonitorWidget *widget = new widgets::MemMonitorWidget();
    widget->init();
    return widget;
}

}