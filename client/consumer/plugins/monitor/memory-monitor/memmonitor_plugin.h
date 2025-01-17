#pragma once

#include "interfaces/monitor_plugin_interface.h"
#include "memmonitor_widget.h"

namespace plugins
{

class MemMonitorPlugin : public MonitorInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MonitorInterface_iid FILE "memory-monitor.json")
    Q_INTERFACES(plugins::MonitorInterface)
public:
    MemMonitorPlugin() = default;
    virtual ~MemMonitorPlugin();

    Q_INVOKABLE virtual void init() override;
    virtual QString name() const override;
    virtual QWidget *widget() const override;
    Q_INVOKABLE virtual void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    widgets::MemMonitorWidget* m_widget;
};

}