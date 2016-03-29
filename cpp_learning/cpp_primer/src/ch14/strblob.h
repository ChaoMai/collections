#ifndef STRBLOG_H_
#define STRBLOG_H_ value

#include <initializer_list>
#include <iostream>
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
  friend bool operator==(const StrBlob &lhs, const StrBlob &rhs);
  friend bool operator!=(const StrBlob &lhs, const StrBlob &rhs);

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

  std::string &operator[](size_t n) { return data->at(n); }
  const std::string &operator[](size_t n) const { return data->at(n); }
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

bool operator==(const StrBlob &lhs, const StrBlob &rhs);
bool operator!=(const StrBlob &lhs, const StrBlob &rhs);

#endif /* ifndef STRBLOG_H_ */
