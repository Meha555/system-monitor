#pragma once

#include "monitor_factory.h"

namespace factories
{

class CpuMonitorFactory : public MonitorFactory
{
public:
    explicit CpuMonitorFactory() = default;
    ~CpuMonitorFactory() = default;

    widgets::MonitorWidget *createMonitorWidget() override;
};

}