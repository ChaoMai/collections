#include "conststrblobptr.h"

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using std::out_of_range;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return lhs.curr == rhs.curr;
}

bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return !(lhs == rhs);
}

bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return lhs.curr == rhs.curr;
}

const string &ConstStrBlobPtr::operator*() {
  auto p = check(curr, "deference past end");
  return (*p)[curr];
}

const string *ConstStrBlobPtr::operator->() {
  return &this->operator*();
}

shared_ptr<const vector<string>> ConstStrBlobPtr::check(
    size_t i, const string &msg) const {
  auto ret = wptr.lock();

  if (!ret) {
    throw runtime_error("unbound StrBlobPtr");
  }

  if (i >= ret->size()) {
    throw out_of_range(msg);
  }

  return ret;
}

const string &ConstStrBlobPtr::deref() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

ConstStrBlobPtr &ConstStrBlobPtr::incr() {
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

ConstStrBlobPtr StrBlob::begin() const { return ConstStrBlobPtr(*this); }

ConstStrBlobPtr StrBlob::end() const {
  auto ret = ConstStrBlobPtr(*this, data->size());
  return ret;
}
