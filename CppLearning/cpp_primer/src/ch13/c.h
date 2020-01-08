#ifndef C_H_
#define C_H_ value

#include <iostream>

class C {
 public:
  C() {
    name_ = c;
    ++c;
    std::cout << "c" << name_ << ": " << __func__ << std::endl;
  }
  C(const int name) : name_(name) {
    std::cout << "c" << name_ << ": " << __func__ << std::endl;
  }
  C(const C &rhs) : name_(c++) {
    std::cout << "copy from c" << rhs.name_ << ", c" << name_ << ": "
              << __func__ << std::endl;
  }
  C &operator=(const C &rhs) {
    std::cout << "copy assign from c" << rhs.name_ << ", c" << name_ << ": "
              << __func__ << std::endl;
    return *this;
  }
  // ~C() { std::cout << "c" << name_ << ": " << __func__ << std::endl; }

  int name_ = 0;
  static int c;
};

int C::c = 10000;

#endif /* ifndef C_H_ */
