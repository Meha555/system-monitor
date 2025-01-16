#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include "monitor_info.pb.h"
#include <QWidget>

namespace widgets
{

class Q_DECL_EXPORT MonitorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonitorWidget(QWidget *parent = nullptr);
    virtual ~MonitorWidget() = default;

    virtual void init() = 0;
    virtual QString name() const = 0;
    virtual void updateInfo(const monitor::proto::MonitorInfo &monitor_info) = 0;

signals:
    void inited();
};

}

#endif // MONITORWIDGET_H
