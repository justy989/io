#!/bin/bash

set -x

git clone -b $(curl -L https://grpc.io/release) https://github.com/grpc/grpc
cd grpc
git submodule update --init
make
make install
cd ..
./build.sh
LD_LIBRARY_PATH=/usr/local/lib ./c_server &
sleep 1
LD_LIBRARY_PATH=/usr/local/lib ./c_client
