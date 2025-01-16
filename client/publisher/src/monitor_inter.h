#pragma once

#include "monitor_info.pb.h"

namespace monitor
{
class MonitorInter
{
public:
    virtual ~MonitorInter() = default;
    virtual void UpdateOnce(monitor::proto::MonitorInfo *monitor_info) = 0;
    virtual void Stop() = 0;
};
} // namespace monitor