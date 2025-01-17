#include "pluginmanager.h"
#include <QDir>
#include <QPluginLoader>

namespace plugins
{

bool PluginManager::loadPlugins(const QString &directory)
{
    if (m_allLoaded) {
        qWarning() << "You cannot load plugins twice and more";
        return false;
    }
    if (directory.isEmpty()) {
        qWarning() << "No plugin directory specified";
        return false;
    }

    QDir dir(directory);
    if (!dir.exists()) {
        qWarning() << "No plugins found";
        return false;
    }
    QStringList pluginFiles = findFiles(dir.absolutePath(), QStringList() << "*.so");
    for (const auto &pluginFile : pluginFiles) {
        if (QLibrary::isLibrary(pluginFile)) {
            QPluginLoader loader(pluginFile);
            QObject *plugin = loader.instance();
            if (!plugin) {
                continue;
            }
            const QJsonObject &metaData = loader.metaData().value("MetaData").toObject();
            qDebug() << "Load plugin:" << metaData["Name"].toString() << "v" << metaData["Version"].toString();
            if (metaData["Name"].toString().endsWith("-monitor")) {
                if (auto monitorPlugin = qobject_cast<MonitorInterface *>(plugin)) {
                    m_monitor_plugins.append(monitorPlugin);
                    m_allLoaded = true;
                    // 异步调用插件的初始化，避免延迟其他插件的加载
                    QMetaObject::invokeMethod(monitorPlugin, "init", Qt::QueuedConnection);
                }
                qWarning() << "Load plugin failed!!!" << loader.errorString() << pluginFile;
                loader.unload();
            }
        }
    }
    if (m_allLoaded) {
        emit allPluginsLoaded();
    }
    return m_allLoaded;
}

QStringList PluginManager::findFiles(const QString &startDir, QStringList filters) const
{
	QStringList files;
	QDir dir(startDir);

	//搜索当前目录符合条件的文件
	foreach (QString file, dir.entryList(filters, QDir::Files))
		files += startDir + '/' + file;

	//搜索当前目录的子目录符合条件的文件
	foreach (QString subdir, dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot))
		files += findFiles(startDir + '/' + subdir, filters);

	return files;
}

}