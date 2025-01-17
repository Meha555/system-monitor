#pragma once

#include "interfaces/monitor_plugin_interface.h"
#include "netmonitor_widget.h"

namespace plugins
{

class NetonitorPlugin : public MonitorInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID MonitorInterface_iid FILE "network-monitor.json")
    Q_INTERFACES(plugins::MonitorInterface)
public:
    NetonitorPlugin() = default;
    virtual ~NetonitorPlugin();

    virtual void init() override;
    virtual QString name() const override;
    virtual QWidget *widget() const override;
    virtual void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    widgets::NetMonitorWidget* m_widget;
};

}