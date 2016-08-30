#include "tcp_socket.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "socket_exception.h"

using std::exception;
using std::runtime_error;
using std::string;

TcpSocket::TcpSocket(const string& addr, unsigned short port) {
  _fd = socket(AF_INET, SOCK_STREAM, 0);
  if (!is_valid()) {
    throw SocketException("create socket error");
  }

  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = inet_addr(addr.c_str());
  _addr.sin_port = htons(port);
}

TcpSocket::~TcpSocket() {
  if (is_valid()) {
    close(_fd);
  }
}

void TcpSocket::Bind() {
  if (is_valid()) {
    if (bind(_fd, reinterpret_cast<sockaddr*>(&_addr), sizeof(sockaddr_in)) ==
        -1) {
      throw SocketException("bind error");
    }
  } else {
    throw SocketException("socket invalid");
  }
}

void TcpSocket::Listen() {
  if (is_valid()) {
    if (listen(_fd, _backlog)) {
      throw SocketException("bind error");
    }
  } else {
    throw SocketException("socket invalid");
  }
}

void TcpSocket::Connect() {
  if (is_valid()) {
    if (connect(_fd, reinterpret_cast<sockaddr*>(&_addr),
                sizeof(sockaddr_in)) == -1) {
      throw SocketException("connect error");
    }
  } else {
    throw SocketException("socket invalid");
  }
}

void TcpSocket::Send(const string& msg) {
  if (is_valid()) {
    auto sz = send(_fd, msg.c_str(), msg.size(), 0);

    if (sz == -1) {
      throw SocketException("send error");
    }
  } else {
    throw SocketException("socket invalid");
  }
}

string TcpSocket::Recv() {
  if (is_valid()) {
    char buf[BUF_SIZE] = {};
    auto sz = recv(_fd, buf, BUF_SIZE, 0);

    if (sz == -1) {
      throw SocketException("receive error");
    }

    return string(buf);
  } else {
    throw SocketException("socket invalid");
  }
}
