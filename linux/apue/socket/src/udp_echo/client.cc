#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int init_client();

int main() {
  init_client();
  return 0;
}

int init_client() {
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

  // loop with sendto
  string tmp;
  while (cin >> tmp) {
    if (sendto(fd, tmp.c_str(), tmp.size(), 0,
               reinterpret_cast<sockaddr*>(&addr), sizeof(sockaddr_in)) < 0) {
      cout << "sendto error" << endl;
      close(fd);
      return -1;
    }

    constexpr int sz = 256;
    char buf[sz] = {};
    auto rc = recvfrom(fd, buf, sizeof(buf), 0, nullptr, nullptr);

    if (rc < 0) {
      cout << "receive error" << endl;
      close(fd);
      return -1;
    } else if (rc == 0) {
      cout << "no messages available" << endl;
      close(fd);
      return 0;
    }

    cout << "from server: " << buf << endl;
  }

  close(fd);
  return 0;
}
