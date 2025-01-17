#pragma once

#include "factory.h"
#include "cpu_load_monitor.h"
#include "cpu_stat_monitor.h"
#include "mem_monitor.h"
#include "net_monitor.h"
#include "cpu_softirq_monitor.h"

namespace monitor
{

class MonitorInter;

template<>
class Factory<MonitorInter>
{
public:
    Factory() = default;
    virtual ~Factory() = default;
    virtual MonitorInter* create() = 0;
};
using MonitorFactory = Factory<MonitorInter>;

class CpuLoadFacotry : public MonitorFactory
{
public:
    CpuLoadFacotry() = default;
    virtual ~CpuLoadFacotry() = default;
    virtual MonitorInter* create() override
    {
        return new CpuLoadMonitor();
    }
};

class CpuStatFacotry : public MonitorFactory
{
public:
    CpuStatFacotry() = default;
    virtual ~CpuStatFacotry() = default;
    virtual MonitorInter* create() override
    {
        return new CpuStatMonitor();
    }
};

class MemFacotry : public MonitorFactory
{
public:
    MemFacotry() = default;
    virtual ~MemFacotry() = default;
    virtual MonitorInter* create() override
    {
        return new MemMonitor();
    }
};

class NetFacotry : public MonitorFactory
{
public:
    NetFacotry() = default;
    virtual ~NetFacotry() = default;
    virtual MonitorInter* create() override
    {
        return new NetMonitor();
    }
};

class SoftIrqFacotry : public MonitorFactory
{
public:
    SoftIrqFacotry() = default;
    virtual ~SoftIrqFacotry() = default;
    virtual MonitorInter* create() override
    {
        return new CpuSoftIrqMonitor();
    }
};

}