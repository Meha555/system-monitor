#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include "monitor_info.pb.h"

namespace widgets
{

class Q_DECL_EXPORT MonitorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorWidget(QWidget *parent = nullptr);
    virtual ~MonitorWidget() = default;

    virtual void init() = 0;
    virtual void updateInfo(const monitor::proto::MonitorInfo &monitor_info);
};

}

#endif // MONITORWIDGET_H
