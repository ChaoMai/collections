#include <algorithm>
#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using std::begin;
using std::cout;
using std::end;
using std::endl;
using std::fill;

int init_server();

int main() {
  init_server();
  return 0;
}

int init_server() {
  // create
  auto fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd < 0) {
    cout << "create socket error" << endl;
    return -1;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(28888);

  // bind
  if (bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(sockaddr_in))) {
    cout << "bind socket error" << endl;
    close(fd);
    return -1;
  }

  // loop with recvfrom
  constexpr int sz = 256;
  char buf[sz] = {};
  long rc;

  sockaddr_in source_addr;
  socklen_t source_addr_size;

  // recvfrom will setup sender's addr
  while ((rc = recvfrom(fd, buf, sizeof(buf), 0,
                        reinterpret_cast<sockaddr*>(&source_addr),
                        &source_addr_size)) > 0) {
    cout << "from client: recvfrom " << rc << " bytes\n";
    cout << buf << endl;

    if (sendto(fd, buf, sizeof(buf), 0,
               reinterpret_cast<sockaddr*>(&source_addr),
               source_addr_size) < 0) {
      cout << "sendto error" << endl;
      close(fd);
      return -1;
    }

    fill(begin(buf), end(buf), 0);
  }

  if (rc < 0) {
    cout << "receive error" << endl;
    close(fd);
    return -1;
  } else if (rc == 0) {
    cout << "no messages available" << endl;
    close(fd);
    return 0;
  }

  close(fd);

  return 0;
}
