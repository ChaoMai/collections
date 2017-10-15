#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TServerSocket.h>

#include "../../gen-cpp/EchoServer.h"

using std::string;
using boost::shared_ptr;

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace echo;

class EchoServerHandler : public EchoServerIf {
public:
    EchoServerHandler() = default;

    void ping(string& _return)
    {
        _count++;
        _return = "pong";
    }

    void echo(EchoMsg& _return, const std::string& str)
    {
        _count++;
        _return.id = _count;
        _return.msg = str;
    }

private:
    int _count = 0;
};

int main(int argc, char* argv[])
{
    int port = 9090;
    shared_ptr<EchoServerHandler> handler(new EchoServerHandler());
    shared_ptr<TProcessor> processor(new EchoServerProcessor(handler));
    shared_ptr<TServerTransport> server_transport(new TServerSocket(port));
    shared_ptr<TTransportFactory> transport_factory(new TBufferedTransportFactory());
    shared_ptr<TProtocolFactory> protocol_factory(new TBinaryProtocolFactory());

    TSimpleServer server(processor, server_transport, transport_factory, protocol_factory);
    server.serve();
    return 0;
}
