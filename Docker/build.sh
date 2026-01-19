#!/bin/bash

echo "Building Ubuntu 24.04 image for VPU performance estimation"
docker build -t perfsim-docker --build-arg USERNAME=$USER --build-arg USER_UID=$UID --build-arg USER_GID=$(id -g $USER) .