#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "monitor_inter.h"
#include "widgets/monitor_widget.h"

class QStackedLayout;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void buildUI();
    void createMonitors();

public slots:
    void updateData(const monitor::proto::MonitorInfo &monitor_info);

signals:
    void monitorCreated(widgets::MonitorWidget *monitors);

private:
    QStackedLayout *m_stackLayout;
    QVector<widgets::MonitorWidget *> m_monitors;

    QString m_host_name;
    monitor::MonitorInter *m_monitorInter;
};

#endif // MAINWINDOW_H
