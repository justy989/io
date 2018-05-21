#!/bin/bash

set -x

protoc --cpp_out=. io.proto
protoc --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin io.proto

g++ -ggdb3 -std=c++11 c_client.cc io.pb.cc io.grpc.pb.cc -o c_client $(PKG_CONFIG_PATH=/usr/local/lib/pkgconfig pkg-config --libs protobuf grpc++ grpc)
g++ -ggdb3 -std=c++11 c_server.cc io.pb.cc io.grpc.pb.cc -o c_server $(PKG_CONFIG_PATH=/usr/local/lib/pkgconfig pkg-config --libs protobuf grpc++ grpc)

g++ -ggdb3 -std=c++11 c_client_async.cc io.pb.cc io.grpc.pb.cc -o c_client_async $(PKG_CONFIG_PATH=/usr/local/lib/pkgconfig pkg-config --libs protobuf grpc++ grpc)
g++ -ggdb3 -std=c++11 c_server_async.cc io.pb.cc io.grpc.pb.cc -o c_server_async $(PKG_CONFIG_PATH=/usr/local/lib/pkgconfig pkg-config --libs protobuf grpc++ grpc)
