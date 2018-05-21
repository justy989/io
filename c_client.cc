#include <cstdio>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "io.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace io;
using namespace std;

int main(int argc, char** argv){
     auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
     std::unique_ptr<IO::Stub> stub = IO::NewStub(channel);

     ClientContext context;

     ResultOut reply;
     CreateFileIn request;
     request.set_filename("tacos.txt");
     request.set_data("This is some data, what do you mean?");
     request.set_mode(Mode::WRITEABLE);

     Status status = stub->create_file(&context, request, &reply);

     if(!status.ok()){
          std::cout << status.error_code() << ": " << status.error_message() << std::endl;
     }else{
          cout << "create_file(): " << reply.success() << std::endl;
     }

     ClientContext context2;

     request.set_filename("burritos.txt");
     request.set_data("This is completely different data!");

     status = stub->create_file(&context2, request, &reply);

     if(!status.ok()){
          std::cout << status.error_code() << ": " << status.error_message() << std::endl;
     }else{
          cout << "create_file(): " << reply.success() << std::endl;
     }

     return 0;
}
