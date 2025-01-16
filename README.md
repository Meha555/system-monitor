# System Monitor

Linux环境下的Linux性能分析监控系统，支持分布式部署。

## 功能

- 对CPU状态、系统负载、软中断、内存信息以及网络接口状态进行监控，数据每三秒刷新一次；

- 以gRPC的方式实现前后端分离，支持在非桌面环境（服务器环境）运行，并可接入不同的前端。

- 提供dockerfile构建镜像，方便快速部署环境；

- 提供C++ SDK，方便嵌入自己的客户端和实现自己的服务端；

- 提供Linux桌面客户端，遵循freedesktop规范，可以托管给systmed，实现自动部署。



## 详细介绍

* 分布式的性能监控系统，支持CPU状态、系统负载、软中断、内存信息以及网络接口状态的监控；
* 使用dockerfile指定相应的cmake，grpc，proto等源码和依赖，构建整个项目环境，易于在多台服务器上部署环境，并编写容器操作的脚本指令，易于启动操作项目所依赖的环境。
* 使用工厂方法实现monitor模块，监控相应的CPU状态、系统负载、软中断、内存信息、网络接口状态，易于为之后扩展更多系统监控；
* 使用protobuf序列化协议，构建项目的数据结构并创建IDL文件;
* 通过grpc框架，构建出相应的server， client，并考虑为了降低耦合性，项目每个模块相互独立，可拆解，只通过调用grpc服务来进行远程连接；
* 为了模拟出真实的性能问题，使用stress工具进行模拟压测，分析相应时刻服务器的cpu状况和中断状况。

## 使用说明

### 后端部署

1、部署数据采集服务：monitord

执行由client/collector构建来的monitord即可。

2、部署数据发布服务：monitor-server

执行由server/cpp或server/go构建来的monitor-server即可。

3、如果需要使用docker：

构建镜像：

```bash
cd docker/build
docker build --network host -f base.dockerfile .
```

进入docker容器：

```bash
./monitor_docker_run.sh
./monitor_docker_into.sh
```

### 前端部署

执行由client/frontend构建而来的monitor-ui即可。

## 项目展示



## TODO

- 零拷贝有用吗？
- widget改成插件
- 定时任务、数据上报