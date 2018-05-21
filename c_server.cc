#include <iostream>
#include <memory>
#include <string>

#include <sys/stat.h>

#include <grpcpp/grpcpp.h>

#include "io.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using io::CreateFileIn;
using io::DeleteFileIn;
using io::ResultOut;
using io::Mode;

const char* mode_to_str(Mode mode){
     switch(mode){
     case io::Mode::READABLE:
          return "readable";
     case io::Mode::WRITEABLE:
          return "writeable";
     case io::Mode::EXECUTABLE:
          return "executable";
     default:
          break;
     }
}

bool file_exists(const std::string& name){
       struct stat buffer;
       return(stat(name.c_str(), &buffer)== 0);
}

class IOServiceImpl final : public io::IO::Service {
  Status create_file(ServerContext* context, const CreateFileIn* request, ResultOut* reply) override {
       std::cout << "create_file: " << request->filename() << " (" << mode_to_str(request->mode()) << ")" << std::endl;
       std::cout << " data: " << request->data() << std::endl;
       if(!file_exists(request->filename())){
            reply->set_success(true);
       }else{
            reply->set_success(false);
       }
       return Status::OK;
  }
  Status delete_file(ServerContext* context, const DeleteFileIn* request, ResultOut* reply) override {
       std::cout << "delete_file: " << request->filename() << std::endl;
       if(file_exists(request->filename())){
            reply->set_success(true);
       }else{
            reply->set_success(false);
       }
       return Status::OK;
  }
};

int main(int argc, char** argv){
     std::string server_address("0.0.0.0:50051");
     IOServiceImpl service;

     ServerBuilder builder;

     builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
     builder.RegisterService(&service);

     std::unique_ptr<Server> server(builder.BuildAndStart());
     std::cout << "Server listening on " << server_address << std::endl;

     server->Wait();
     return 0;
}
