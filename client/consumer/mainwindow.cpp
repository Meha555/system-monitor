#include "mainwindow.h"
#include "widgets/monitor_widget.h"
#include <QDebug>
#include <QFrame>
#include <QPushButton>
#include <QStackedLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_stackLayout(new QStackedLayout())
    , m_monitorInter(new monitor::MonitorInter(this))
{
    connect(m_monitorInter, &monitor::MonitorInter::inited, [this](QString host_name) {
        m_host_name = host_name;
    });
    connect(m_monitorInter, &monitor::MonitorInter::monitorCreated, [this](widgets::MonitorWidget *monitor) {
        m_monitors.append(monitor);
    });
    connect(m_monitorInter, &monitor::MonitorInter::started, this, &MainWindow::buildUI);
    connect(m_monitorInter, &monitor::MonitorInter::dataUpdated, this, &MainWindow::updateData);

    if (!m_monitorInter->init()) {
        qFatal("monitor init failed!");
    }
    m_monitorInter->start();
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

    for (auto &monitor : m_monitors) {
        m_stackLayout->addWidget(monitor);
        monitor->setParent(wMain);
        QPushButton *btn = new QPushButton(QString("%1's %2").arg(m_host_name).arg(monitor->name()), this);
        btn->setFont(font);
        connect(btn, &QPushButton::clicked, [&]() {
            m_stackLayout->setCurrentIndex(m_stackLayout->indexOf(monitor));
            monitor->show();
        });
        lPanel->addWidget(btn);
    }
}

void MainWindow::updateData(const monitor::proto::MonitorInfo &monitor_info)
{
    for (auto &monitor : m_monitors) {
        monitor->updateInfo(monitor_info);
    }
}