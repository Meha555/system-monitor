#!/usr/bin/env bash

set -e

cd "$(dirname "${BASH_SOURCE[0]}")"

THREAD_NUM=$(nproc)

# https://github.com/google/glog/releases/tag/v0.7.1.tar.gz
# Install glog.
VERSION="0.7.1"
PKG_NAME="glog-${VERSION}.tar.gz"

tar xzf "${PKG_NAME}"

pushd glog-${VERSION}
    mkdir build && cd build
    cmake ..    -DCMAKE_PREFIX_PATH=/usr         \
                -DBUILD_SHARED_LIBS=ON           \
                -DCMAKE_BUILD_TYPE=Release       \
                -DCMAKE_INSTALL_PREFIX=/usr/local/
    make -j${THREAD_NUM}
    make install
popd

ldconfig

# cleanup
rm -rf $PKG_NAME glog-$VERSION
