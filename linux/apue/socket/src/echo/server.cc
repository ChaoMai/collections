#include <algorithm>
#include <arpa/inet.h>  // for ntohl(), inet_addr()
#include <cstddef>
#include <iostream>
#include <netinet/in.h>  // for sockaddr_in
#include <sys/socket.h>  // for socket()
#include <unistd.h>      // for close()

using std::begin;
using std::cout;
using std::end;
using std::endl;
using std::fill;
using std::size_t;

int init_server();
void print_info(const sockaddr_in&);

int main() {
  init_server();
  return 0;
}

int init_server() {
  // create
  auto fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    cout << "create socket error" << endl;
    return -1;
  }

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(18888);

  // bind
  if (bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(sockaddr_in)) < 0) {
    cout << "bind socket error" << endl;
    close(fd);
    return -1;
  }

  // listen
  if (listen(fd, 1) < 0) {
    cout << "listen socket error" << endl;
    close(fd);
    return -1;
  }

  // accept
  auto cfd = accept(fd, 0, 0);
  if (cfd < 0) {
    cout << "accept socket error" << endl;
    close(fd);
    return -1;
  }

  // recv with loop
  constexpr int sz = 256;
  char buf[sz] = {};
  long rc;

  while ((rc = recv(cfd, buf, sizeof(buf), 0)) > 0) {
    cout << "from client: recv " << rc << " bytes\n";
    cout << buf << endl;

    if (send(cfd, buf, sizeof(buf), 0) < 0) {
      cout << "send error" << endl;
      close(cfd);
      close(fd);
      return -1;
    }

    fill(begin(buf), end(buf), 0);
  }

  if (rc < 0) {
    cout << "receive error" << endl;
    close(cfd);
    close(fd);
    return -1;
  } else if (rc == 0) {
    cout << "no messages available" << endl;
    close(cfd);
    close(fd);
    return 0;
  }

  close(cfd);
  close(fd);
  return 0;
}

void print_info(const sockaddr_in& addr) {
  cout << "address: " << inet_ntoa(addr.sin_addr) << endl;
  cout << "port number: " << ntohs(addr.sin_port) << endl;
}
