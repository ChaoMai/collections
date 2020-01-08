#include "strblobptr.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using std::out_of_range;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  return lhs.curr == rhs.curr;
}

bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  return lhs.curr == rhs.curr;
}

bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  return !(lhs == rhs);
}

StrBlobPtr operator+(const StrBlobPtr &lhs, size_t n) {
  StrBlobPtr ret = lhs;
  ret += n;
  return ret;
}

StrBlobPtr operator-(const StrBlobPtr &lhs, size_t n) {
  StrBlobPtr ret = lhs;
  ret -= n;
  return ret;
}

size_t operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  return lhs.curr - rhs.curr;
}

string &StrBlobPtr::operator*() const {
  auto p = check(curr, "deference past end");
  return (*p)[curr];
}

string *StrBlobPtr::operator->() const { return &this->operator*(); }

shared_ptr<vector<string>> StrBlobPtr::check(size_t i,
                                             const string &msg) const {
  auto ret = wptr.lock();

  if (!ret) {
    throw runtime_error("unbound StrBlobPtr");
  }

  if (i >= ret->size()) {
    throw out_of_range(msg);
  }

  return ret;
}

string &StrBlobPtr::deref() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

StrBlobPtr &StrBlobPtr::incr() {
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

StrBlobPtr &StrBlobPtr::operator++() {
  // 本身就有可能时尾后指针
  // 对于尾后指针不应该执行++
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

StrBlobPtr &StrBlobPtr::operator--() {
  --curr;
  check(curr, "increment past end of StrBlobPtr");
  return *this;
}

StrBlobPtr StrBlobPtr::operator++(int) {
  StrBlobPtr ret = *this;
  ++*this;
  return ret;
}

StrBlobPtr StrBlobPtr::operator--(int) {
  StrBlobPtr ret = *this;
  --*this;
  return ret;
}

StrBlobPtr &StrBlobPtr::operator+=(size_t n) {
  check(curr + n, "increment past end of StrBlobPtr");
  curr += n;
  return *this;
}

StrBlobPtr &StrBlobPtr::operator-=(size_t n) {
  check(curr - n, "decrement past head of StrBlobPtr");
  curr -= n;
  return *this;
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end() {
  auto ret = StrBlobPtr(*this, data->size());
  return ret;
}
