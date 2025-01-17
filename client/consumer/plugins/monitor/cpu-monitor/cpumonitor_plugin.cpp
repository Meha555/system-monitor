#include "cpumonitor_plugin.h"

namespace plugins
{

CpuMonitorPlugin::~CpuMonitorPlugin()
{
    delete m_widget;
}

void CpuMonitorPlugin::init()
{
    m_widget = new widgets::CpuMonitorWidget();
    m_widget->init();
    connect(this, &CpuMonitorPlugin::infoUpdated, m_widget, &widgets::CpuMonitorWidget::updateInfo);
    emit inited();
}

QString CpuMonitorPlugin::name() const
{
    return QStringLiteral("CPU");
}

QWidget *CpuMonitorPlugin::widget() const
{
    return m_widget;
}

void CpuMonitorPlugin::updateInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    emit infoUpdated(monitor_info);
}

}