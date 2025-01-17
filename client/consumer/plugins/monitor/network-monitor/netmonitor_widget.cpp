#include "netmonitor_widget.h"
#include "components/highlight_delegate.h"
#include "models/net_model.h"
#include <QGridLayout>

namespace widgets
{

NetMonitorWidget::NetMonitorWidget(MonitorWidget *parent)
    : MonitorWidget(parent)
    , m_net_box(new components::TableBox(tr("Monitor Network"), new models::NetModel(this), false, this))
{
}

void NetMonitorWidget::init()
{
    m_net_box->setItemDelegate(new components::HighlightDelegate(this));

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(m_net_box);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    m_net_box->display();
}

void NetMonitorWidget::updateInfo(const monitor::proto::MonitorInfo &monitor_info)
{
    qobject_cast<models::NetModel *>(m_net_box->model())->updateMonitorInfo(monitor_info);
}

}