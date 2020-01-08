#ifndef DEBUG_DELETE_H_
#define DEBUG_DELETE_H_

#include <iostream>

class DebugDelete {
 public:
  DebugDelete(std::ostream& s = std::cerr) : os(s) {}
  template <typename T>
  void operator()(T* p) const {
    os << "deleting unique_ptr" << std::endl;
    delete p;
  }

 private:
  std::ostream& os;
};

#endif
