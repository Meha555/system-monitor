#include "mainwindow.h"
#include "factories/monitor_factory.h"
#include "factories/cpumonitor_factory.h"
#include "factories/memmonitor_factory.h"
#include "factories/monitor_factory.h"
#include "factories/netmonitor_factory.h"
#include "factories/softirqmonitor_factory.h"
#include "widgets/monitor_widget.h"
#include <QDebug>
#include <QFrame>
#include <QPushButton>
#include <QStackedLayout>
#include <qlogging.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_stackLayout(new QStackedLayout())
    , m_monitorInter(new monitor::MonitorInter(this))
{
    connect(this, &MainWindow::monitorCreated, [this](widgets::MonitorWidget *monitor) {
        m_monitors.append(monitor);
    });
    connect(m_monitorInter, &monitor::MonitorInter::inited, [this](QString host_name) {
        m_host_name = host_name;
    });
    // connect(m_monitorInter, &monitor::MonitorInter::started, this, &MainWindow::buildUI);
    connect(m_monitorInter, &monitor::MonitorInter::dataUpdated, this, &MainWindow::updateData);

    buildUI();

    // 异步地启动后端监控Stub
    QThreadPool::globalInstance()->start([this] {
        if (!m_monitorInter->init()) {
            qCritical("monitor init failed!");
            exit(0);
        }
        m_monitorInter->start();
    });
}

MainWindow::~MainWindow()
{
    m_monitorInter->stop();
}

void MainWindow::buildUI()
{
    QFont font("Consolas", 15, 40);
    QHBoxLayout *lPanel = new QHBoxLayout();
    QFrame *wBtnPannel = new QFrame(this);
    wBtnPannel->setLayout(lPanel);

    QVBoxLayout *lMain = new QVBoxLayout();
    lMain->addWidget(wBtnPannel, 1);
    lMain->addLayout(m_stackLayout, 4);

    QWidget *wMain = new QWidget(this);
    wMain->setLayout(lMain);
    setCentralWidget(wMain);

    createMonitors();

    for (auto &monitor : m_monitors) {
        m_stackLayout->addWidget(monitor);
        monitor->setParent(wMain);
        QPushButton *btn = new QPushButton(QString("%1's %2").arg(m_host_name).arg(monitor->name()), this);
        btn->setFont(font);
        connect(btn, &QPushButton::clicked, [&]() {
            m_stackLayout->setCurrentIndex(m_stackLayout->indexOf(monitor));
            monitor->show();
        });
        lPanel->addWidget(btn, 4);
    }
    QPushButton *btn = new QPushButton(tr("Refresh"), this);
    connect(btn, &QPushButton::clicked, m_monitorInter, &monitor::MonitorInter::refresh);
    lPanel->addWidget(btn, 1);
}

void MainWindow::createMonitors()
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

void MainWindow::updateData(const monitor::proto::MonitorInfo &monitor_info)
{
    for (auto &monitor : m_monitors) {
        monitor->updateInfo(monitor_info);
    }
}