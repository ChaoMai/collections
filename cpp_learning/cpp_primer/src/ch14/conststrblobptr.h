#ifndef ConstStrBlobPtr_H_
#define ConstStrBlobPtr_H_

#include "strblob.h"

#include <memory>
#include <string>

class ConstStrBlobPtr {
  friend bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
  friend bool operator==(const ConstStrBlobPtr &lhs,
                         const ConstStrBlobPtr &rhs);
  friend bool operator!=(const ConstStrBlobPtr &lhs,
                         const ConstStrBlobPtr &rhs);

 public:
  ConstStrBlobPtr() : curr(0) {}
  ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
  const std::string &deref() const;
  ConstStrBlobPtr &incr();
  const std::string &operator*();
  const std::string *operator->();

 private:
  std::shared_ptr<const std::vector<std::string>> check(
      size_t, const std::string &) const;
  std::weak_ptr<const std::vector<std::string>> wptr;
  size_t curr;
};

bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

#endif /* ifndef ConstStrBlobPtr_H_ */
