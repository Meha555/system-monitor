#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowTitle("System Monitor");
    w.setWindowOpacity(0.8);
    w.setMinimumWidth(1000);
    w.show();

    return app.exec();
}