#pragma once

#include "monitor_factory.h"

namespace factories
{

class SoftIrqMonitorFactory : public MonitorFactory
{
public:
    explicit SoftIrqMonitorFactory() = default;
    ~SoftIrqMonitorFactory() = default;

    widgets::MonitorWidget *createMonitorWidget() override;
};

}