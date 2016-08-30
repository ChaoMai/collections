#ifndef HASPTR_PTR_H_
#define HASPTR_PTR_H_

#include <cstddef>
#include <string>

class HasPtrPtr {
 public:
  HasPtrPtr(const std::string& s = std::string())
      : ps(new std::string(s)), use(new std::size_t(1)) {}

  HasPtrPtr(const HasPtrPtr& rhs) : ps(rhs.ps), use(rhs.use) { ++*use; }

  HasPtrPtr(HasPtrPtr&& rhs) : ps(rhs.ps), use(rhs.use) {
    rhs.ps = nullptr;
    rhs.use = nullptr;
  }

  HasPtrPtr& operator=(const HasPtrPtr& rhs) {
    ++*rhs.use;

    if (--*use == 0) {
      delete ps;
      delete use;
    }

    ps = rhs.ps;
    use = rhs.use;

    return *this;
  }

  HasPtrPtr& operator=(HasPtrPtr&& rhs) {
    ps = rhs.ps;
    use = rhs.use;
    rhs.ps = nullptr;
    rhs.use = nullptr;
  }

  ~HasPtrPtr() {
    if (--*use == 0) {
      delete ps;
      delete use;
    }
  }

 private:
  std::string* ps;
  std::size_t* use;
};

#endif  // HASPTR_PTR_H_
