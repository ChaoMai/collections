// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "EchoServer.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::echo;

class EchoServerHandler : virtual public EchoServerIf {
 public:
  EchoServerHandler() {
    // Your initialization goes here
  }

  void ping(std::string& _return) {
    // Your implementation goes here
    printf("ping\n");
  }

  void echo(EchoMsg& _return, const std::string& str) {
    // Your implementation goes here
    printf("echo\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<EchoServerHandler> handler(new EchoServerHandler());
  shared_ptr<TProcessor> processor(new EchoServerProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
