#include "monitor_inter.h"
#include <QDebug>
#include <QtConcurrent/QtConcurrent>

#include "factories/cpumonitor_factory.h"
#include "factories/memmonitor_factory.h"
#include "factories/monitor_factory.h"
#include "factories/netmonitor_factory.h"
#include "factories/softirqmonitor_factory.h"
#include "rpc_client.h"

static const QString g_config_file = QStringLiteral("monitor.conf");

namespace monitor
{

MonitorInter::MonitorInter(QObject *parent)
    : QObject(parent)
    , m_config(nullptr)
    , m_stop(false)
{
    qRegisterMetaType<monitor::proto::MonitorInfo>();
    readConfig();
}

void MonitorInter::readConfig()
{
    if (m_config) {
        return;
    }
    m_config.reset(new QSettings(g_config_file, QSettings::IniFormat));
    QString ip = m_config->value("/server/ip").toString();
    QString port = m_config->value("/server/port").toString();
    m_config_map["ip"] = ip;
    m_config_map["port"] = port;
}

bool MonitorInter::init()
{
    QString address = QString("%1:%2")
                          .arg(m_config_map["ip"])
                          .arg(m_config_map["port"]);
    qInfo() << "Connecting to server:" << address;
    m_monitorMgrClient = std::make_unique<MonitorManagementClient>(address.toStdString());
    m_monitorClient = std::make_unique<MonitorClient>(address.toStdString());

    monitor::proto::MonitorInfo monitor_info;
    uint8_t count = 5;
    while (!m_monitorMgrClient->GetMonitorInfo(&monitor_info) && --count > 0) {
        qWarning() << "Get monitor info failed, retrying for last " << count << " times";
        QThread::sleep(2);
    }
    if (count <= 0) {
        qWarning() << "Failed to get monitor info, connection probably broken";
        return false;
    }

    m_host_name = QString::fromStdString(monitor_info.name());
    emit inited(m_host_name);
    return true;
}

void MonitorInter::start()
{
    Q_ASSERT(m_monitorMgrClient);
    Q_ASSERT(m_monitorClient);
    createMonitors();

    emit started();

    QtConcurrent::run([this]() -> int {
        // TODO SubscribeMonitorInfo跑起来就不会主动退出，所以需要一个取消机制
        return m_monitorClient->SubscribeMonitorInfo();
    });
    m_future = QtConcurrent::run([this]() -> int {
        // monitor::proto::MonitorInfo monitor_info;
        while (!m_stop) {
            // monitor_info.Clear();
            // m_monitorMgrClient->GetMonitorInfo(&monitor_info);
            // qWarning() << "====" << QString::fromStdString(monitor_info.DebugString());
            // emit dataUpdated(monitor_info);
            auto monitor_info = m_monitorClient->FetchMonitorInfo();
            emit dataUpdated(monitor_info);
            // QThread::sleep(3);
        }
        return 0;
    });
}

void MonitorInter::stop()
{
    m_stop.store(true);
    qInfo() << "Exiting with code:" << m_future.result();
}

void MonitorInter::createMonitors()
{
    QSharedPointer<factories::MonitorFactory> factory;

    factory.reset(new factories::CpuMonitorFactory());
    emit monitorCreated(factory->createMonitorWidget());

    factory.reset(new factories::MemMonitorFactory());
    emit monitorCreated(factory->createMonitorWidget());

    factory.reset(new factories::NetMonitorFactory());
    emit monitorCreated(factory->createMonitorWidget());

    factory.reset(new factories::SoftIrqMonitorFactory());
    emit monitorCreated(factory->createMonitorWidget());
}

}