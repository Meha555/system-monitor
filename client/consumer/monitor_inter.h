#pragma once

#include "monitor_info.pb.h"
#include "rpc_client.h"
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

public slots:
    bool init();
    void start();
    void stop();
    void refresh();

signals:
    void inited(QString host_name);
    void started();
    void dataUpdated(const monitor::proto::MonitorInfo &monitor_info);

private:
    QString m_host_name;
    QScopedPointer<QSettings> m_config;
    QMap<QString, QString> m_config_map;
    std::atomic<bool> m_stop;
    QFuture<int> m_future;

    RpcClient *m_rpc_client;
};

}

Q_DECLARE_METATYPE(monitor::proto::MonitorInfo)