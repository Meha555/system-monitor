#include <csignal>
#include <memory>
#include <string>
#include <thread>

#include "client/rpc_client.h"
#include "cpu_load_monitor.h"
#include "cpu_softirq_monitor.h"
#include "cpu_stat_monitor.h"
#include "mem_monitor.h"
#include "net_monitor.h"

#include "inicpp/inicpp.hpp"
#include "monitor_info.pb.h"
#include <gflags/gflags.h>
#include <glog/logging.h>

DEFINE_string(conf,
              "monitor.conf",
              "Server config file");

int main(int argc, char *argv[])
{
    std::signal(SIGPIPE, SIG_IGN); // daemon应该忽略SIGPIPE信号
    google::InitGoogleLogging(argv[0]);
    FLAGS_colorlogtostderr = true; // 启用彩色日志
    FLAGS_logtostderr = true; // 默认输出标准错误
    google::InstallFailureSignalHandler();
    ::gflags::ParseCommandLineFlags(&argc, &argv, true);

    inicpp::IniManager conf(FLAGS_conf);
    const std::string ip = conf["server"]["ip"];
    const std::string port = conf["server"]["port"];

    std::vector<std::shared_ptr<monitor::MonitorInter>> monitors;
    monitors.emplace_back(new monitor::CpuSoftIrqMonitor());
    monitors.emplace_back(new monitor::CpuLoadMonitor());
    monitors.emplace_back(new monitor::CpuStatMonitor());
    monitors.emplace_back(new monitor::MemMonitor());
    monitors.emplace_back(new monitor::NetMonitor());

    const char *user_name = getenv("USER");

    monitor::MonitorManagementClient monitorMrgClient(ip + ":" + port);
    monitor::MonitorClient monitorClient(ip + ":" + port);

    bool sendOnce = false;
    // 发布数据
    while (true) {
        monitor::proto::MonitorInfo monitor_info;
        monitor_info.set_name(std::string(user_name ? user_name : "unknown"));

        for (auto &mon : monitors) {
            mon->UpdateOnce(&monitor_info);
        }

        if (!sendOnce) {
            monitorMrgClient.SetMonitorInfo(monitor_info);
            sendOnce = true;
        }
        monitorClient.PublishMonitorInfo(monitor_info);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return 0;
}
