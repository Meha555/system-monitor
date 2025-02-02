#pragma once

#include "monitor_info.pb.h"
#include "rpc_client.h"
#include "widgets/monitor_widget.h"
#include <QFuture>
#include <QMap>
#include <QSettings>

class QSettings;
namespace monitor
{

class MonitorInter : public QObject
{
    Q_OBJECT
public:
    explicit MonitorInter(QObject *parent = nullptr);

    void readConfig();

private:
    void createMonitors();

public slots:
    bool init();
    void start();
    void stop();

signals:
    void inited(QString host_name);
    void monitorCreated(widgets::MonitorWidget *monitors);
    void started();
    void dataUpdated(const monitor::proto::MonitorInfo &monitor_info);

private:
    QString m_host_name;
    QScopedPointer<QSettings> m_config;
    QMap<QString, QString> m_config_map;
    std::atomic<bool> m_stop;
    QFuture<int> m_future;

    std::unique_ptr<MonitorClient> m_monitorClient;
    std::unique_ptr<MonitorManagementClient> m_monitorMgrClient;
};

}

Q_DECLARE_METATYPE(monitor::proto::MonitorInfo)