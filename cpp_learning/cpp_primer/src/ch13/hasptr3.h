#ifndef HASPTR3_H_
#define HASPTR3_H_

#include <iostream>
#include <string>

#define NDEBUG

class HasPtr3 {
  friend void swap(HasPtr3&, HasPtr3&);
  friend bool operator<(const HasPtr3& lhs, const HasPtr3& rhs);

 public:
  HasPtr3(const std::string& s = std::string())
      : ps(new std::string(s)), i(0) {}
  HasPtr3(const HasPtr3& hp) : ps(new std::string(*hp.ps)), i(hp.i) {
#ifndef NDEBUG
    std::cout << "copied" << std::endl;
#endif
  }
  HasPtr3(HasPtr3&& hp) noexcept : ps(hp.ps), i(hp.i) {
    hp.ps = nullptr;
#ifndef NDEBUG
    std::cout << "moved" << std::endl;
#endif
  }

  // = 4s
  // mixed 4.8s
  HasPtr3& operator=(const HasPtr3& rhs) {
    auto newp = new std::string(*rhs.ps);
    delete ps;
    ps = newp;
    i = rhs.i;
#ifndef NDEBUG
    std::cout << "copy assigned" << std::endl;
#endif
    return *this;
  }

  // move 0.7s
  // mixed 4.8s
  HasPtr3& operator=(HasPtr3&& rhs) noexcept {
    if (this != &rhs) {
      delete ps;
      ps = rhs.ps;
      i = rhs.i;
      rhs.ps = nullptr;
#ifndef NDEBUG
      std::cout << "move assigned" << std::endl;
#endif
    }
    return *this;
  }

  // = 6s
  // move 2.5s
  // mixed 8.8s
  // HasPtr3& operator=(HasPtr3 rhs) {
  // swap(*this, rhs);
  // #ifndef NDEBUG
  // std::cout << "assigned" << std::endl;
  // #endif
  // return *this;
  // }

  ~HasPtr3() { delete ps; }

 private:
  std::string* ps;
  int i;
};

inline void swap(HasPtr3& lhs, HasPtr3& rhs) {
  using std::swap;
  swap(lhs.ps, rhs.ps);  // swap the pointers, not the string data
  swap(lhs.i, rhs.i);    // swap the int members

#ifndef NDEBUG
  std::cout << "swapped" << std::endl;
#endif
}

#endif /* ifndef HASPTR3_H_ */
