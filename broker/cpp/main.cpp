#include <csignal>
#include <fcntl.h>
#include <string>
#include <unistd.h>

#include "inicpp/inicpp.hpp"
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <grpc/grpc.h>
#include <grpcpp/server_builder.h>

#include "rpc_server.h"

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

static void start_server(const std::string &ip, const std::string &port)
{
    grpc::ServerBuilder builder;
    builder.AddListeningPort(ip + ":" + port, grpc::InsecureServerCredentials());

    monitor::MonitorServiceImpl grpc_server;
    builder.RegisterService(&grpc_server);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();
}

int main(int argc, char *argv[])
{
    // daemonize(); // FIXME

    google::InitGoogleLogging(argv[0]);
    FLAGS_colorlogtostderr = false; // 关闭彩色日志
    google::LogToStderr();
    google::InstallFailureSignalHandler();

    ::gflags::ParseCommandLineFlags(&argc, &argv, true);
    inicpp::IniManager conf(FLAGS_conf);
    const std::string ip = conf["server"]["ip"];
    const std::string port = conf["server"]["port"];
    const google::LogSeverity log_level = static_cast<google::LogSeverity>(conf["server"]["log_level"].operator int());
    const std::string log_path = conf["server"]["log_path"];

    google::SetLogDestination(log_level, log_path.c_str());

    start_server(ip, port);
    return 0;
}