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
     ClientContext context2;

     ResultOut reply;
     CreateFileIn request;

     void* got_tag;
     bool ok = false;

     Status status;
     grpc::CompletionQueue cq;

     request.set_filename("tacos.txt");
     request.set_data("This is some data, what do you mean?");
     request.set_mode(Mode::WRITEABLE);

     std::unique_ptr<grpc::ClientAsyncResponseReader<ResultOut> > remote_process_call(stub->Asynccreate_file(&context, request, &cq));

     remote_process_call->Finish(&reply, &status, (void*)1);

     cq.Next(&got_tag, &ok);
     if (ok && got_tag == (void*)1) {
          if(!status.ok()){
               std::cout << status.error_code() << ": " << status.error_message() << std::endl;
          }else{
               cout << "create_file(): " << reply.success() << std::endl;
          }
     }

     request.set_filename("burritos.txt");
     request.set_data("This is completely different data!");

     std::unique_ptr<grpc::ClientAsyncResponseReader<ResultOut> > remote_process_call2(stub->Asynccreate_file(&context, request, &cq));
     remote_process_call2->Finish(&reply, &status, (void*)1);

     cq.Next(&got_tag, &ok);
     if (ok && got_tag == (void*)1) {
          if(!status.ok()){
               std::cout << status.error_code() << ": " << status.error_message() << std::endl;
          }else{
               cout << "create_file(): " << reply.success() << std::endl;
          }
     }

     return 0;
}
