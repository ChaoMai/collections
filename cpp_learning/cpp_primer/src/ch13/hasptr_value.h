#ifndef HASPTR_VALUE_H_
#define HASPTR_VALUE_H_

#include <string>

class HasPtrValue {
 public:
  HasPtrValue(const std::string &s = std::string())
      : ps(new std::string(s)), i(0) {}

  HasPtrValue(const HasPtrValue &rhs)
      : ps(new std::string(*rhs.ps)), i(rhs.i) {}

  HasPtrValue(HasPtrValue &&rhs) : ps(rhs.ps), i(rhs.i) {
    rhs.ps = nullptr;
    rhs.i = 0;
  }

  HasPtrValue &operator=(const HasPtrValue &rhs) {
    auto newp = new std::string(*rhs.ps);
    delete ps;

    ps = newp;
    i = rhs.i;

    return *this;
  }

  HasPtrValue &operator=(HasPtrValue &&rhs) {
    // ps = rhs.ps;
    // i = rhs.i;

    // rhs.ps = nullptr;
    // rhs.i = 0;

    // return *this;

    if (this != &rhs) {
      ps = rhs.ps;
      i = rhs.i;

      rhs.ps = nullptr;
      rhs.i = 0;
    }

    return *this;
  }

  ~HasPtrValue() { delete ps; }

  // private:
  std::string *ps;
  int i;
};

#endif  // HASPTR_VALUE_H_
