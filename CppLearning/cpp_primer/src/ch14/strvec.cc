#include "strvec.h"

#include <initializer_list>
#include <memory>
#include <string>
#include <utility>

using std::allocator;
using std::for_each;
using std::initializer_list;
using std::pair;
using std::string;
using std::uninitialized_copy;

std::allocator<std::string> StrVec::alloc;

bool operator==(const StrVec &lhs, const StrVec &rhs) {
  return (lhs.size() == rhs.size()) &&
         equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const StrVec &lhs, const StrVec &rhs) { return !(lhs == rhs); }

void StrVec::push_back(const string &s) {
  chk_n_alloc();
  alloc.construct(first_free++, s);
}

pair<string *, string *> StrVec::alloc_n_copy(const string *b,
                                              const string *e) {
  auto data = alloc.allocate(static_cast<allocator<string>::size_type>(e - b));
  return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free() {
  if (elements) {
    // for (auto p = first_free; p != elements;) {
    // alloc.destroy(--p);
    // }
    // 此处alloc不同capture，因为不是自动变量
    for_each(elements, first_free, [](string &p) { alloc.destroy(&p); });
    alloc.deallocate(elements,
                     static_cast<allocator<string>::size_type>(cap - elements));
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

StrVec::StrVec(initializer_list<string> li) {
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

StrVec &StrVec::operator=(initializer_list<string> li) {
  auto newsize = li.size();
  auto newdata = alloc.allocate(newsize);
  auto dest = newdata;
  auto elem = li.begin();
  free();
  for (size_t i = 0; i < newsize; ++i) {
    alloc.construct(dest++, std::move(*elem++));
  }
  elements = newdata;
  first_free = dest;
  cap = elements + newsize;
  return *this;
}

StrVec &StrVec::operator=(const StrVec &rhs) {
  auto p = alloc_n_copy(rhs.elements, rhs.first_free);
  free();
  elements = p.first;
  first_free = p.second;
  cap = p.second;
  return *this;
}

string &StrVec::operator[](size_t n) { return elements[n]; }

const string &StrVec::operator[](size_t n) const { return elements[n]; }

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
