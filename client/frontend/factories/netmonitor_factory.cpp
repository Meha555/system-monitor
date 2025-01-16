#include "netmonitor_factory.h"
#include "widgets/netmonitor_widget.h"

namespace factories
{

widgets::MonitorWidget *NetMonitorFactory::createMonitorWidget()
{
    widgets::MonitorWidget *widget = new widgets::NetMonitorWidget();
    widget->init();
    return widget;
}

}