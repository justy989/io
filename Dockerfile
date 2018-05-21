FROM ubuntu:16.04
FROM grpc/cxx:latest

ADD c_client /
ADD c_server /
ADD run_docker.sh /
ADD run_client.sh /
ADD build.sh /
ADD c_client.cc /
ADD c_server.cc /
ADD greeter.proto /

ENV LD_LIBRARY_PATH=/usr/local/lib

RUN apt-get update
RUN apt-get install -y libprotobuf-java protobuf-compiler
RUN apt-get install -y build-essential autoconf libtool pkg-config
RUN apt-get install -y libgflags-dev libgtest-dev
RUN apt-get install -y clang libc++-dev

CMD ["/bin/bash", "run_docker.sh"]
