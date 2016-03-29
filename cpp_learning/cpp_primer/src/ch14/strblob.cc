#include "strblob.h"

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using std::initializer_list;
using std::make_shared;
using std::out_of_range;
using std::runtime_error;
using std::shared_ptr;
using std::string;
using std::vector;

bool operator==(const StrBlob &lhs, const StrBlob &rhs);
bool operator!=(const StrBlob &lhs, const StrBlob &rhs);

bool operator==(const StrBlob &lhs, const StrBlob &rhs) {
  return *lhs.data < *rhs.data;
}

bool operator!=(const StrBlob &lhs, const StrBlob &rhs) {
  return !(lhs == rhs);
}

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> li)
    : data(make_shared<vector<string>>(li)) {}

void StrBlob::check(size_type i, const string &msg) const {
  if (i >= data->size()) {
    throw out_of_range(msg);
  }
}

string &StrBlob::front() {
  check(0, "back on empty StrBlob");
  return data->front();
}

string &StrBlob::front() const {
  check(0, "back on empty StrBlob");
  return data->front();
}

string &StrBlob::back() {
  check(0, "back on empty StrBlob");
  return data->back();
}

string &StrBlob::back() const {
  check(0, "back on empty StrBlob");
  return data->back();
}

void StrBlob::pop_back() {
  check(0, "pop_back on empty StrBlob");
  return data->pop_back();
}
