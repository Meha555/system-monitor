#ifndef MEMMONITORWIDGET_H
#define MEMMONITORWIDGET_H

#include "components/tablebox.h"
#include "monitor_widget.h"

namespace widgets
{

class MemMonitorWidget : public MonitorWidget
{
    Q_OBJECT
public:
    explicit MemMonitorWidget(MonitorWidget *parent = nullptr);

    void init() override;
    QString name() const override
    {
        return QStringLiteral("Memory");
    }
    void updateInfo(const monitor::proto::MonitorInfo &monitor_info) override;

private:
    components::TableBox *m_mem_box;
};

}

#endif // MEMMONITORWIDGET_H
