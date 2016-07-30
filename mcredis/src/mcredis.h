#ifndef MCREDIS_H_
#define MCREDIS_H_

#include <string>

#include "tcp_socket.h"

class Mcredis {
 public:
  Mcredis(const std::string& addr = "", unsigned short port = 0);
  ~Mcredis();

 private:
  TcpSocket _tcp_socket;
};

#endif
