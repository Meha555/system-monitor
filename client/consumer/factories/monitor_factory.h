#pragma once

#include "widgets/monitor_widget.h"

namespace factories
{

class MonitorFactory
{
public:
    explicit MonitorFactory() = default;
    virtual ~MonitorFactory() = default;

    virtual widgets::MonitorWidget *createMonitorWidget() = 0;
};

}