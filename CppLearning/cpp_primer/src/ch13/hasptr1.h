#ifndef HASPTR1_H_
#define HASPTR1_H_ value

#include <iostream>
#include <string>

class HasPtr1 {
  friend void swap(HasPtr1 &lhs, HasPtr1 &rhs);

 public:
  HasPtr1(const std::string &s = std::string())
      : ps(new std::string(s)), i(0) {}
  HasPtr1(const HasPtr1 &rhs) : ps(new std::string(*rhs.ps)), i(rhs.i) {
    std::cout << "copied" << std::endl;
  }
  HasPtr1 &operator=(const HasPtr1 &rhs) {
    // 异常安全，如果throw bal_alloc，下面的delete就不会执行。
    auto newp = new std::string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
    return *this;
  }
  bool operator<(const HasPtr1 &rhs) { return *ps < *rhs.ps; }
  std::string getStr() { return *ps; }
  ~HasPtr1() { delete ps; }

 private:
  int i;
  std::string *ps;
};

inline void swap(HasPtr1 &lhs, HasPtr1 &rhs) {
  using std::swap;
  swap(lhs.ps, rhs.ps);
  swap(lhs.i, rhs.i);
  std::cout << "swapped" << std::endl;
}

#endif /* ifndef HASPTR1_H_ */
