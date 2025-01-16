#ifndef NETMONITORWIDGET_H
#define NETMONITORWIDGET_H

#include "components/tablebox.h"
#include "monitor_widget.h"

namespace widgets
{

class NetMonitorWidget : public MonitorWidget
{
    Q_OBJECT
public:
    explicit NetMonitorWidget(MonitorWidget *parent = nullptr);

    void init() override;
    QString name() const override
    {
        return QStringLiteral("Network");
    }
    void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    components::TableBox *m_net_box;
};

}

#endif // NETMONITORWIDGET_H
