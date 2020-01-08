#ifndef STRVEC_H_
#define STRVEC_H_ value

#include <algorithm>
#include <initializer_list>
#include <string>
#include <utility>

class StrVec {
 public:
  StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
  StrVec(std::initializer_list<std::string>);
  StrVec(const StrVec &);
  StrVec(StrVec &&s) noexcept : elements(s.elements),
                                first_free(s.first_free),
                                cap(s.cap) {
    s.elements = s.first_free = s.cap = nullptr;
  }
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

std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string &s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

std::pair<std::string *, std::string *> StrVec::alloc_n_copy(
    const std::string *b, const std::string *e) {
  auto data = alloc.allocate(
      static_cast<std::allocator<std::string>::size_type>(e - b));
  return {data, std::uninitialized_copy(b, e, data)};
}

void StrVec::free() {
  if (elements) {
    // for (auto p = first_free; p != elements;) {
    // alloc.destroy(--p);
    // }
    // 此处alloc不同capture，因为不是自动变量
    std::for_each(elements, first_free,
                  [](std::string &p) { alloc.destroy(&p); });
    alloc.deallocate(
        elements,
        static_cast<std::allocator<std::string>::size_type>(cap - elements));
  }
}

void StrVec::reallocate() {
  // copy
  // size_t new_size = size() ? 2 * size() : 1;
  // auto newb = alloc.allocate(new_size * 2);
  // auto newe = uninitialized_copy(elements, cap, newb);
  // free();
  // elements = newb;
  // first_free = newe;
  // cap = elements + new_size;

  // move
  // auto newcapatity = size() ? 2 * size() : 1;
  // auto newdata = alloc.allocate(newcapatity);
  // auto dest = newdata;
  // auto elem = elements;
  // for (size_t i = 0; i != size(); ++i) {
  // alloc.construct(dest++, std::move(*elem++));
  // }
  // free();
  // elements = newdata;
  // first_free = dest;
  // cap = elements + newcapatity;

  // simpler move
  size_t new_size = size() ? 2 * size() : 1;
  auto newb = alloc.allocate(new_size * 2);
  auto newe = uninitialized_copy(make_move_iterator(elements),
                                 make_move_iterator(cap), newb);
  free();
  elements = newb;
  first_free = newe;
  cap = elements + new_size;
}

StrVec::StrVec(std::initializer_list<std::string> li) {
  size_t newsize = li.size();
  auto newdata = alloc.allocate(newsize);
  auto dest = newdata;
  auto elem = li.begin();
  for (size_t i = 0; i < newsize; ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  elements = newdata;
  first_free = dest;
  cap = elements + newsize;
}

StrVec::StrVec(const StrVec &s) {
  auto p = alloc_n_copy(s.elements, s.first_free);
  elements = p.first;
  first_free = p.second;
  cap = p.second;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
  auto p = alloc_n_copy(rhs.elements, rhs.first_free);
  free();
  elements = p.first;
  first_free = p.second;
  cap = p.second;
  return *this;
}

StrVec::~StrVec() { free(); }

void StrVec::reserve(size_t newcapatity) {
  if (newcapatity <= capacity()) {
    return;
  }

  auto newdata = alloc.allocate(newcapatity);
  auto dest = newdata;
  auto elem = elements;
  for (size_t i = 0; i < size(); ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  elements = newdata;
  first_free = dest;
  cap = elements + newcapatity;
}

void StrVec::resize(size_t newsize) {
  auto newdata = alloc.allocate(newsize);
  auto dest = newdata;
  auto elem = elements;
  for (size_t i = 0; i < newsize; ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  elements = newdata;
  first_free = dest;
  cap = elements + newsize;
}

#endif /* ifndef STRVEC_H_ */
