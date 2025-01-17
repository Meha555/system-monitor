#ifndef NETMONITORWIDGET_H
#define NETMONITORWIDGET_H

#include "components/tablebox.h"
#include "plugins/monitor/monitor_widget.h"

namespace widgets
{

class NetMonitorWidget : public MonitorWidget
{
    Q_OBJECT
public:
    explicit NetMonitorWidget(MonitorWidget *parent = nullptr);

    void init() override;
    void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    components::TableBox *m_net_box;
};

}

#endif // NETMONITORWIDGET_H
