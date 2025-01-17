#include "netmonitor_plugin.h"

namespace plugins
{

NetonitorPlugin::~NetonitorPlugin()
{
    delete m_widget;
}

void NetonitorPlugin::init()
{
    m_widget = new widgets::NetMonitorWidget();
    m_widget->init();
    connect(this, &NetonitorPlugin::infoUpdated, m_widget, &widgets::NetMonitorWidget::updateInfo);
    emit inited();
}

QString NetonitorPlugin::name() const
{
    return QStringLiteral("Network");
}

QWidget *NetonitorPlugin::widget() const
{
    return m_widget;
}

void NetonitorPlugin::updateInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    emit infoUpdated(monitor_info);
}

}