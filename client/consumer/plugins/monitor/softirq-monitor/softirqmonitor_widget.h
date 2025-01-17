#ifndef SOFTIRQMONITORWIDGET_H
#define SOFTIRQMONITORWIDGET_H

#include "components/tablebox.h"
#include "plugins/monitor/monitor_widget.h"

namespace widgets
{

class SoftIrqMonitorWidget : public MonitorWidget
{
    Q_OBJECT
public:
    explicit SoftIrqMonitorWidget(MonitorWidget *parent = nullptr);

    void init() override;
    void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    components::TableBox *m_softirq_box;
};

}

#endif // SOFTIRQMONITORWIDGET_H
