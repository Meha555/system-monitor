#pragma once

#include "interfaces/monitor_plugin_interface.h"
#include "cpumonitor_widget.h"

namespace plugins
{

class CpuMonitorPlugin : public MonitorInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MonitorInterface_iid FILE "cpu-monitor.json")
    Q_INTERFACES(plugins::MonitorInterface)
public:
    CpuMonitorPlugin() = default;
    virtual ~CpuMonitorPlugin();

    Q_INVOKABLE virtual void init() override;
    virtual QString name() const override;
    virtual QWidget *widget() const override;
    Q_INVOKABLE virtual void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    widgets::CpuMonitorWidget* m_widget;
};

}