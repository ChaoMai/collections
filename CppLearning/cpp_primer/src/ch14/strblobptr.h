#ifndef STRBLOBPTR_H_
#define STRBLOBPTR_H_

#include <memory>
#include <string>

#include "strblob.h"

class StrBlobPtr {
  friend bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
  friend bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
  friend bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
  friend StrBlobPtr operator+(const StrBlobPtr &lhs, size_t n);
  friend StrBlobPtr operator-(const StrBlobPtr &lhs, size_t n);
  friend size_t operator-(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

 public:
  StrBlobPtr() : curr(0) {}
  StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
  std::string &deref() const;
  StrBlobPtr &incr();
  StrBlobPtr &operator++();
  StrBlobPtr &operator--();
  StrBlobPtr operator++(int);
  StrBlobPtr operator--(int);
  StrBlobPtr &operator+=(size_t);
  StrBlobPtr &operator-=(size_t);
  std::string &operator*() const;
  std::string *operator->() const;

 private:
  std::shared_ptr<std::vector<std::string>> check(size_t,
                                                  const std::string &) const;
  std::weak_ptr<std::vector<std::string>> wptr;
  size_t curr;
};

bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
StrBlobPtr operator+(const StrBlobPtr &lhs, size_t n);
StrBlobPtr operator-(const StrBlobPtr &lhs, size_t n);

#endif /* ifndef STRBLOBPTR_H_ */
