#pragma once

#include "interfaces/monitor_plugin_interface.h"
#include "softirqmonitor_widget.h"

namespace plugins
{

class SoftIrqMonitorPlugin : public MonitorInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MonitorInterface_iid FILE "softirq-monitor.json")
    Q_INTERFACES(plugins::MonitorInterface)
public:
    SoftIrqMonitorPlugin() = default;
    virtual ~SoftIrqMonitorPlugin();

    virtual void init() override;
    virtual QString name() const override;
    virtual QWidget *widget() const override;
    virtual void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    widgets::SoftIrqMonitorWidget* m_widget;
};

}