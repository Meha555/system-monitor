FROM docker.m.daocloud.io/library/ubuntu:18.04

LABEL maintainer="meha555"

# 避免apt-get在安装软件包时出现交互式提示，仅在构建时使用
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Asia/Shanghai

SHELL ["/bin/bash", "-c"]

# 换源
# COPY apt/sources.list /etc/apt/
COPY apt/monitor.list /etc/apt/sources.list.d/

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y \
    apt-utils \
    curl \
    openssh-server \
    build-essential \
    # libprotobuf-dev \
    # libgrpc++-dev \
    # protobuf-compiler \
    # protobuf-compiler-grpc \
    gcc \
    g++ \
    make \
    cmake \
    libgoogle-glog-dev \
    net-tools \
    vim \
    stress

RUN apt-get install -y \
    libc-ares-dev \
    libssl-dev \
    net-tools \
    zlib1g-dev

# RUN apt-get install -y  \
#     libx11-xcb1 \
#     libfreetype6 \
#     libdbus-1-3 \
#     libfontconfig1 \
#     libxkbcommon0   \
#     libxkbcommon-x11-0 \
#     qtbase5-dev \
#     qtchooser \
#     qt5-qmake \
#     qtbase5-dev-tools

COPY install/cmake /tmp/install/cmake
RUN /tmp/install/cmake/install_cmake.sh

COPY install/protobuf /tmp/install/protobuf
RUN /tmp/install/protobuf/install_protobuf.sh

COPY install/abseil /tmp/install/abseil
RUN /tmp/install/abseil/install_abseil.sh

COPY install/grpc /tmp/install/grpc
RUN /tmp/install/grpc/install_grpc.sh

COPY install/glog /tmp/install/glog
RUN /tmp/install/glog/install_glog.sh

# RUN apt-get install -y python3-pip
# RUN pip3 install cuteci -i https://mirrors.aliyun.com/pypi/simple

# COPY install/qt /tmp/install/qt
# RUN /tmp/install/qt/install_qt.sh

RUN apt-get clean && apt-get autoclean && rm -rf /tmp/install/*