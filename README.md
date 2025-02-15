# System Monitor

Linux性能监控系统，支持分布式部署。

## 功能

- 对CPU状态、系统负载、软中断、内存信息以及网络接口状态进行监控，数据每三秒刷新一次；

- 前后端分离，前后端以gRPC通信，支持在非桌面环境（服务器环境）运行，并可接入不同的前端。

- 获取数据支持主动获取和发布订阅

- 提供dockerfile构建镜像，方便快速部署环境；

- 提供C++和Go的SDK，方便嵌入自己的客户端和实现自己的服务端；

- 提供Linux桌面客户端，遵循freedesktop规范，可以托管给systmed，实现自动部署。

![architecture](architecture.png)

## 详细介绍

* 分布式的性能监控系统，支持CPU状态、系统负载、软中断、内存信息以及网络接口状态的监控；
* 使用dockerfile指定相应的cmake，grpc，proto等源码和依赖，构建整个项目环境，易于在多台服务器上部署环境，并编写容器操作的脚本指令，易于启动操作项目所依赖的环境。
* 使用protobuf序列化协议，构建项目的数据结构并创建IDL文件;
* 通过grpc框架，构建出相应的server， client，并考虑为了降低耦合性，项目每个模块相互独立，可拆解，只通过调用grpc服务来进行远程连接；
* 通过基本的请求响应模式实现数据的主动上报和拉取；通过HTTP/2的服务端流式响应实现了数据的发布订阅；
* 使用工厂方法实现monitor模块，监控相应的CPU状态、系统负载、软中断、内存信息、网络接口状态，易于为之后扩展更多系统监控；

## 使用说明

目前有3个分支：

- master：使用主动获取的方式，客户端没有拆分插件
- publish-dev：使用发布订阅的方式，客户端有拆分插件
- plugin-dev：使用主动获取的方式，客户端有拆分插件

可以使用 `stress` 命令来压力测试。

### 后端部署

1、部署数据采集服务：monitord

执行由client/publisher构建来的monitord即可。

2、部署数据转发服务：monitor-broker

执行由broker/cpp或broker/go构建来的monitor-broker即可。

3、如果需要使用docker：

构建镜像：

```bash
cd docker/images
docker build -t monitor:1.0 --network host -f monitor.dockerfile .
```

进入docker容器：

```bash
./monitor_docker_run.sh
./monitor_docker_into.sh
```

### 前端部署

执行由client/frontend构建而来的monitor-ui即可。

## TODO

- 心跳机制（目前仅在启动时发送一次心跳用于探测连接，且后续的心跳仅在publish-dev分支需要实现）
- 定时任务