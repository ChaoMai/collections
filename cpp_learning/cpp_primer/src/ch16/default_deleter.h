#ifndef DEFAULT_DELETER_
#define DEFAULT_DELETER_

class DefaultDeleter {
 public:
  template <typename T>
  void operator()(T* p) const {
    delete p;
  }
};

#endif /* ifndef DEFAULT_DELETER_ */
