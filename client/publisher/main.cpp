#include <csignal>
#include <memory>
#include <string>
#include <thread>
#include <fcntl.h>

#include "inicpp/inicpp.hpp"
#include <gflags/gflags.h>
#include <glog/logging.h>
#include "client/rpc_client.h"
#include "monitor_info.pb.h"
#include "monitor_factory.h"

DEFINE_string(conf,
              "monitor.conf",
              "Server config file");

static void daemonize()
{
    daemon(0, 1); // daemon化
    std::signal(SIGPIPE, SIG_IGN); // daemon应该忽略SIGPIPE信号
    int fd = -1;
    if (-1 != (fd = open("/dev/null", O_RDWR))) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

int main(int argc, char *argv[])
{
    // daemonize();

    ::google::InitGoogleLogging(argv[0]);
    FLAGS_colorlogtostderr = true; // 启用彩色日志
    FLAGS_logtostderr = true; // 默认输出标准错误
    ::google::InstallFailureSignalHandler();
    ::gflags::ParseCommandLineFlags(&argc, &argv, true);

    inicpp::IniManager conf(FLAGS_conf);
    const std::string ip = conf["server"]["ip"];
    const std::string port = conf["server"]["port"];

    // 用工厂隐藏创建细节
    auto softIrpFactory = new monitor::SoftIrqFacotry();
    auto cpuLoadFactory = new monitor::CpuLoadFacotry();
    auto cpuStatFactory = new monitor::CpuStatFacotry();
    auto memFactory = new monitor::MemFacotry();
    auto netFactory = new monitor::NetFacotry();

    std::vector<std::shared_ptr<monitor::MonitorInter>> monitors;
    monitors.emplace_back(softIrpFactory->create());
    monitors.emplace_back(cpuLoadFactory->create());
    monitors.emplace_back(cpuStatFactory->create());
    monitors.emplace_back(memFactory->create());
    monitors.emplace_back(netFactory->create());

    char *user_name = getenv("USER");
    monitor::RpcClient rpc_client(ip + ":" + port);
    while (true) {
        monitor::proto::MonitorInfo monitor_info;
        monitor_info.set_name(std::string(user_name ? user_name : "unknown"));

        for (auto &mon : monitors) {
            mon->UpdateOnce(&monitor_info);
        }
        rpc_client.SetMonitorInfo(monitor_info);
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    return 0;
}
