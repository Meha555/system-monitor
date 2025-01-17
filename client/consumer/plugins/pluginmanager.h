#pragma once

#include <QObject>
#include "interfaces/monitor_plugin_interface.h"

namespace plugins
{

class PluginManager : public QObject
{
    Q_OBJECT
public:
    ~PluginManager() = default;
    bool loadPlugins(const QString &directory);

    static PluginManager &Instance() {
        static PluginManager instance;
        return instance;
    }

    QVector<MonitorInterface *> monitorPlugins() const {
        return m_monitor_plugins;
    }

private:
    QStringList findFiles(const QString &startDir, QStringList filters) const;

signals:
    void allPluginsLoaded();

private:
    explicit PluginManager();

    bool m_allLoaded;
    QVector<MonitorInterface *> m_monitor_plugins;
};

}