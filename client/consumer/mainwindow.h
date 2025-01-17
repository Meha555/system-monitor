#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "monitor_inter.h"

class QStackedLayout;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void buildUI();

public slots:
    void updateData(const monitor::proto::MonitorInfo &monitor_info);

private:
    QStackedLayout *m_stackLayout;
    // QVector<widgets::MonitorWidget *> m_monitors;

    QString m_host_name;
    monitor::MonitorInter *m_monitorInter;
};

#endif // MAINWINDOW_H
