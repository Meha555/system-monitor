#ifndef CPUMONITORWIDGET_H
#define CPUMONITORWIDGET_H

#include "components/tablebox.h"
#include "plugins/monitor/monitor_widget.h"

namespace widgets
{

class CpuMonitorWidget : public widgets::MonitorWidget
{
    Q_OBJECT
public:
    explicit CpuMonitorWidget(widgets::MonitorWidget *parent = nullptr);

    void init() override;
    void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    components::TableBox *m_cpu_load_box;
    components::TableBox *m_cpu_stat_box;
};

}

#endif // CPUMONITORWIDGET_H
