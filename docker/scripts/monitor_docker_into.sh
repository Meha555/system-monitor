#!/usr/bin/env bash
set -e

xhost +local:root 1>/dev/null 2>&1
docker exec \
    -u root \
    -it monitor \
    /bin/bash
xhost -local:root 1>/dev/null 2>&1
