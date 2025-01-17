#pragma once

#include <QObject>
#include <QString>
#include "monitor_info.pb.h"

// Q_DECLARE_METATYPE(monitor::proto::MonitorInfo)

class QWidget;
namespace plugins
{

#define MonitorInterface_iid "com.monitor.MonitorInterface"

class MonitorInterface : public QObject
{
    Q_OBJECT
public:
    explicit MonitorInterface() = default;
    // {
    //     qRegisterMetaType<monitor::proto::MonitorInfo>();
    // }
    virtual ~MonitorInterface() = default;

    virtual void init() = 0;
    virtual QString name() const = 0;
    virtual QWidget *widget() const = 0;
    virtual void updateInfo(const monitor::proto::MonitorInfo &monitor_info) = 0;

signals:
    void inited();
    void infoUpdated(const monitor::proto::MonitorInfo &monitor_info);
};

}
Q_DECLARE_INTERFACE(plugins::MonitorInterface, MonitorInterface_iid)