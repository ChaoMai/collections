#ifndef HASPTR_H_
#define HASPTR_H_

#include <array>
#include <string>

class HasPtr {
 public:
  HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) {}
  HasPtr(const HasPtr &rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {}
  HasPtr &operator=(const HasPtr &rhs) {
    auto newp = new std::string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
  }
  ~HasPtr() { delete ps; }

  std::string *ps;
  int i;
  int arr[10];
  std::array<int, 10> sarr;
};

#endif /* ifndef HASPTR_H_ */
