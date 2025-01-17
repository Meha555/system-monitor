#include "softirqmonitor_plugin.h"

namespace plugins
{

SoftIrqMonitorPlugin::~SoftIrqMonitorPlugin()
{
    delete m_widget;
}

void SoftIrqMonitorPlugin::init()
{
    m_widget = new widgets::SoftIrqMonitorWidget();
    m_widget->init();
    connect(this, &SoftIrqMonitorPlugin::infoUpdated, m_widget, &widgets::SoftIrqMonitorWidget::updateInfo);
    emit inited();
}

QString SoftIrqMonitorPlugin::name() const
{
    return QStringLiteral("SoftIrq");
}

QWidget *SoftIrqMonitorPlugin::widget() const
{
    return m_widget;
}

void SoftIrqMonitorPlugin::updateInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    emit infoUpdated(monitor_info);
}

}