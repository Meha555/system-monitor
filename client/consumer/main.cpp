#include <QApplication>
#include <QTimer>
#include "mainwindow.h"
#include "plugins/pluginmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    MainWindow w;
    plugins::PluginManager::Instance().loadPlugins("plugins");
    w.connect(&plugins::PluginManager::Instance(), &plugins::PluginManager::allPluginsLoaded,
              &w, &MainWindow::buildUI);
    w.setWindowTitle("System Monitor @ " + QSysInfo::machineHostName());
    w.setWindowOpacity(0.8);
    w.setMinimumWidth(1000);

    QTimer::singleShot(1000, [&w] () { w.show(); });

    return app.exec();
}