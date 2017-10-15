#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../../gen-cpp/EchoServer.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using boost::shared_ptr;

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace echo;

int main(int argc, char* argv[])
{
    shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    EchoServerClient client(protocol);

    transport->open();
    string str;
    while (cin >> str) {
        if (str == "ping") {
            string ret;
            client.ping(ret);
            cout << ret << endl;
        } else if (str.length() > 0) {
            EchoMsg echo_msg;
            client.echo(echo_msg, str);
            cout << echo_msg.id << " " << echo_msg.msg << endl;
        } else {
            continue;
        }
    }

    transport->close();
    return 0;
}
