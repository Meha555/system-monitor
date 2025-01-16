#pragma once

#include "monitor_factory.h"

namespace factories
{

class NetMonitorFactory : public MonitorFactory
{
public:
    explicit NetMonitorFactory() = default;
    ~NetMonitorFactory() = default;

    widgets::MonitorWidget *createMonitorWidget() override;
};

}