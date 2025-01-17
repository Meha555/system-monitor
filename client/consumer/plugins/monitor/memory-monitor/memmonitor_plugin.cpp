#include "memmonitor_plugin.h"

namespace plugins
{

MemMonitorPlugin::~MemMonitorPlugin()
{
    delete m_widget;
}

void MemMonitorPlugin::init()
{
    m_widget = new widgets::MemMonitorWidget();
    m_widget->init();
    connect(this, &MemMonitorPlugin::infoUpdated, m_widget, &widgets::MemMonitorWidget::updateInfo);
    emit inited();
}

QString MemMonitorPlugin::name() const
{
    return QStringLiteral("Memory");
}

QWidget *MemMonitorPlugin::widget() const
{
    return m_widget;
}

void MemMonitorPlugin::updateInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    emit infoUpdated(monitor_info);
}

}