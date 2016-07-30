#ifndef TCP_SOCKET_H_
#define TCP_SOCKET_H_

#include <netinet/in.h>
#include <unistd.h>

#include <string>

constexpr int BUF_SIZE = 1024;

class TcpSocket {
 public:
  TcpSocket(const std::string& addr = "", unsigned short port = 0);
  TcpSocket(const TcpSocket&) = delete;
  TcpSocket& operator=(const TcpSocket&) = delete;
  ~TcpSocket();

  void Bind();
  void Listen();
  int Accept();

  void Connect();

  void Send(const std::string&);
  std::string Recv();

 private:
  int _fd = -1;
  int _backlog = 1;
  sockaddr_in _addr;

  bool is_valid() { return _fd != -1; }
};

#endif
