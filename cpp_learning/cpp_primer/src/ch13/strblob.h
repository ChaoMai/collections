#ifndef STRBLOG_H_
#define STRBLOG_H_ value

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob {
  friend class StrBlobPtr;
  friend class ConstStrBlobPtr;

 public:
  using size_type = std::vector<std::string>::size_type;
  StrBlob();
  StrBlob(std::initializer_list<std::string> li);
  StrBlob(const StrBlob &rhs) {
    data = std::make_shared<std::vector<std::string>>(*rhs.data);
  }
  StrBlob &operator=(const StrBlob &rhs) {
    data = std::make_shared<std::vector<std::string>>(*rhs.data);
    return *this;
  }
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const std::string &t) { data->push_back(t); }
  void push_back(std::string &&t) { data->push_back(std::move(t)); }
  void pop_back();
  std::string &front();
  std::string &front() const;
  std::string &back();
  std::string &back() const;
  // as these function need to access the member function of StrBlob, define
  // later
  StrBlobPtr begin();
  StrBlobPtr end();
  ConstStrBlobPtr begin() const;
  ConstStrBlobPtr end() const;

 private:
  std::shared_ptr<std::vector<std::string>> data;
  void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

StrBlob::StrBlob(std::initializer_list<std::string> li)
    : data(std::make_shared<std::vector<std::string>>(li)) {}

void StrBlob::check(size_type i, const std::string &msg) const {
  if (i >= data->size()) {
    throw std::out_of_range(msg);
  }
}

std::string &StrBlob::front() {
  check(0, "back on empty StrBlob");
  return data->front();
}

std::string &StrBlob::front() const {
  check(0, "back on empty StrBlob");
  return data->front();
}

std::string &StrBlob::back() {
  check(0, "back on empty StrBlob");
  return data->back();
}

std::string &StrBlob::back() const {
  check(0, "back on empty StrBlob");
  return data->back();
}

void StrBlob::pop_back() {
  check(0, "pop_back on empty StrBlob");
  return data->pop_back();
}

bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

class StrBlobPtr {
  friend bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

 public:
  StrBlobPtr() : curr(0) {}
  StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
  std::string &deref() const;
  StrBlobPtr &incr();

 private:
  std::shared_ptr<std::vector<std::string>> check(size_t,
                                                  const std::string &) const;
  std::weak_ptr<std::vector<std::string>> wptr;
  size_t curr;
};

bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  return lhs.curr == rhs.curr;
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(
    size_t i, const std::string &msg) const {
  auto ret = wptr.lock();

  if (!ret) {
    throw std::runtime_error("unbound StrBlobPtr");
  }

  if (i >= ret->size()) {
    throw std::out_of_range(msg);
  }

  return ret;
}

std::string &StrBlobPtr::deref() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

StrBlobPtr &StrBlobPtr::incr() {
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end() {
  auto ret = StrBlobPtr(*this, data->size());
  return ret;
}

bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

class ConstStrBlobPtr {
  friend bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

 public:
  ConstStrBlobPtr() : curr(0) {}
  ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
  const std::string &deref() const;
  ConstStrBlobPtr &incr();

 private:
  std::shared_ptr<std::vector<std::string>> check(size_t,
                                                  const std::string &) const;
  std::weak_ptr<std::vector<std::string>> wptr;
  size_t curr;
};

bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return lhs.curr == rhs.curr;
}

std::shared_ptr<std::vector<std::string>> ConstStrBlobPtr::check(
    size_t i, const std::string &msg) const {
  auto ret = wptr.lock();

  if (!ret) {
    throw std::runtime_error("unbound StrBlobPtr");
  }

  if (i >= ret->size()) {
    throw std::out_of_range(msg);
  }

  return ret;
}

const std::string &ConstStrBlobPtr::deref() const {
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

#endif /* ifndef STRBLOG_H_ */
