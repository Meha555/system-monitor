#pragma once

#include "monitor_factory.h"

namespace factories
{

class MemMonitorFactory : public MonitorFactory
{
public:
    explicit MemMonitorFactory() = default;
    ~MemMonitorFactory() = default;

    widgets::MonitorWidget *createMonitorWidget() override;
};

}