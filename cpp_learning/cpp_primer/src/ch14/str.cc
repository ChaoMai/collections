#include "str.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

using std::cout;
using std::endl;
using std::equal;
using std::for_each;
using std::pair;
using std::uninitialized_copy;

std::allocator<char> Str::alloc;

Str::Str() { chk_n_alloc(); }

Str::Str(const char* p) {
  // while (*p == '\0')
  // 不可行，未拷贝空字符
  while (true) {
    chk_n_alloc();
    *first_free++ = *p;
    ++p;

    if (*p == '\0') {
      *first_free++ = *p;
      break;
    }
  }
}

Str::Str(const int n, const char ch) {
  auto i = n;
  while (i != 0) {
    chk_n_alloc();
    *first_free++ = ch;
  }
}

Str::Str(const Str& s) {
  auto p = alloc_n_copy(s.elements, s.first_free);
  elements = p.first;
  first_free = p.second;
  cap = p.second;
  cout << "copied" << endl;
}

Str::Str(Str&& s) noexcept : elements(s.elements),
                             first_free(s.first_free),
                             cap(s.cap) {
  s.elements = s.first_free = s.cap = nullptr;
  cout << "moved" << endl;
}

Str& Str::operator=(const Str& rhs) {
  free();
  auto p = alloc_n_copy(rhs.elements, rhs.first_free);
  elements = p.first;
  first_free = p.second;
  cap = p.second;
  cout << "copy assigned" << endl;
  return *this;
}

Str& Str::operator=(Str&& rhs) noexcept {
  if (this != &rhs) {
    free();
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
    cout << "move assigned" << endl;
  }
  return *this;
}

Str::~Str() { free(); }

void Str::push_back(char ch) {
  chk_n_alloc();
  *first_free++ = ch;
}

void Str::append(const char* str) {
  while (true) {
    chk_n_alloc();
    *first_free++ = *str;
    ++str;

    if (*str == '\0') {
      *first_free++ = *str;
      break;
    }
  }
}

pair<char*, char*> Str::alloc_n_copy(const char* b, const char* e) {
  auto newdata = alloc.allocate(static_cast<size_t>(e - b));
  return {newdata, uninitialized_copy(b, e, newdata)};
}

void Str::reallocate() {
  auto newsize = size() ? 2 * size() : 1;
  auto newdata = alloc.allocate(newsize);

  auto dest = newdata;
  auto elem = elements;

  for (size_t i = 0; i != size(); ++i) {
    alloc.construct(dest++, *elem++);
  }

  free();

  elements = newdata;
  first_free = dest;
  cap = elements + newsize;
}

void Str::free() {
  if (elements) {
    for_each(elements, first_free, [](char& ch) { alloc.destroy(&ch); });
    alloc.deallocate(elements, capacity());
  }
}

std::ostream& operator<<(std::ostream& os, const Str& str) {
  // 既然初始化时已经拷贝了空字符，直接输出即可
  os << str.c_str();
  return os;
}

bool operator==(const Str& lhs, const Str& rhs) {
  return (lhs.size() == rhs.size()) &&
         (equal(lhs.begin(), lhs.end(), rhs.begin()));
}

bool operator!=(const Str& lhs, const Str& rhs) { return !(lhs == rhs); }

char& Str::operator[](size_t n) { return elements[n]; }

const char& Str::operator[](size_t n) const { return elements[n]; }
