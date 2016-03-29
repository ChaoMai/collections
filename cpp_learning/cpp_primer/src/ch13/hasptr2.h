#ifndef HASPTR_2_
#define HASPTR_2_ value

#include <iostream>
#include <string>

class HasPtr2 {
  friend void swap(HasPtr2 &lhs, HasPtr2 &rhs);

 public:
  HasPtr2(const std::string &s = std::string())
      : ps(new std::string(s)), i(0), use(new size_t(1)) {}
  HasPtr2(const HasPtr2 &rhs) : ps(rhs.ps), i(rhs.i), use(rhs.use) { ++*use; }
  HasPtr2 &operator=(const HasPtr2 &rhs) {
    ++*rhs.use;
    if (--*use == 0) {
      delete ps;
      delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
  }
  ~HasPtr2() {
    if (--*use == 0) {
      delete ps;
      delete use;
    }
  }

 private:
  std::string *ps;
  int i;
  size_t *use;
};

inline void swap(HasPtr2 &lhs, HasPtr2 &rhs) {
  using std::swap;
  swap(lhs.ps, rhs.ps);
  swap(lhs.i, rhs.i);
  std::cout << "swapped" << std::endl;
}

#endif /* ifndef HASPTR_2_ */
