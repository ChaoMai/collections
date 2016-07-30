#ifndef SOCKET_EXCEPTION_H_
#define SOCKET_EXCEPTION_H_

#include <exception>
#include <string>

class SocketException : public std::exception {
 public:
  explicit SocketException(const std::string& s) : _s(s) {}
  const char* what() const noexcept;

 private:
  std::string _s;
};

#endif
