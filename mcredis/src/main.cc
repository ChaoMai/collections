#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "tcp_socket.h"

#include "mcredis.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;

int main() {
  TcpSocket socket("127.0.0.1", 6379);
  socket.Connect();
  socket.Send("*1\r\n$4\r\nPING\r\n");
  string msg = socket.Recv();
  cout << msg << endl;
}
