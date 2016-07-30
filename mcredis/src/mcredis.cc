#include "mcredis.h"

#include <string>

#include "tcp_socket.h"

using std::string;

Mcredis::Mcredis(const string& addr, unsigned short port)
    : _tcp_socket(addr, port) {}
