#ifndef STRVEC_H_
#define STRVEC_H_ value

#include <algorithm>
#include <initializer_list>
#include <string>
#include <utility>

class StrVec {
  friend bool operator==(const StrVec &, const StrVec &);
  friend bool operator!=(const StrVec &, const StrVec &);

 public:
  StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(std::initializer_list<std::string>);
  StrVec(const StrVec &);
  StrVec(StrVec &&s) noexcept : elements(s.elements),
                                first_free(s.first_free),
                                cap(s.cap) {
    s.elements = s.first_free = s.cap = nullptr;
  }
  StrVec &operator=(std::initializer_list<std::string>);
  StrVec &operator=(const StrVec &);
  StrVec &operator=(StrVec &&rhs) noexcept {
    if (this != &rhs) {
      free();
      elements = rhs.elements;
      first_free = rhs.first_free;
      cap = rhs.cap;
      rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
  }
  std::string &operator[](std::size_t n);
  const std::string &operator[](std::size_t n) const;
  ~StrVec();
  void push_back(const std::string &);
  size_t size() const { return static_cast<size_t>(first_free - elements); }
  size_t capacity() const { return static_cast<size_t>(cap - elements); }
  std::string *begin() const { return elements; }
  std::string *end() const { return first_free; }
  void reserve(size_t newcapatity);
  void resize(size_t newsize);

 private:
  static std::allocator<std::string> alloc;
  void chk_n_alloc() {
    if (size() == capacity()) {
      reallocate();
    }
  }
  std::pair<std::string *, std::string *> alloc_n_copy(const std::string *,
                                                       const std::string *);
  void free();
  void reallocate();
  std::string *elements;
  std::string *first_free;
  std::string *cap;
};

bool operator==(const StrVec &, const StrVec &);
bool operator!=(const StrVec &, const StrVec &);

#endif /* ifndef STRVEC_H_ */
