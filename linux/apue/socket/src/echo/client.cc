#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int init_client();
void print_info(const sockaddr_in&);

int main() {
  init_client();
  return 0;
}

int init_client() {
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

  // connect
  if (connect(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(sockaddr)) < 0) {
    cout << "connect error" << endl;
    close(fd);
    return -1;
  }

  // send with loop
  string tmp;
  while (cin >> tmp) {
    // char is 1 byte
    // cannot use sizeof(cstr) here, it (a pointer) is always 8 bytes
    if (send(fd, tmp.c_str(), tmp.size(), 0) < 0) {
      cout << "send error" << endl;
      close(fd);
      return -1;
    }

    constexpr int sz = 256;
    char buf[sz] = {};
    auto rc = recv(fd, buf, sizeof(buf), 0);

    if (rc == 0) {
      cout << "no messages available" << endl;
      close(fd);
      return 0;
    } else if (rc < 0) {
      cout << "receive error" << endl;
      close(fd);
      return -1;
    }

    cout << "from server: " << buf << endl;
  }

  close(fd);

  return 0;
}

void print_info(const sockaddr_in& addr) {
  cout << "address: " << inet_ntoa(addr.sin_addr) << endl;
  cout << "port number: " << ntohs(addr.sin_port) << endl;
}
