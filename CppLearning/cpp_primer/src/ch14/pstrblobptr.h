#ifndef PSTRBLOBPTR_H_
#define PSTRBLOBPTR_H_

#include <string>

#include "strblobptr.h"

class PStrBlobPtr {
 public:
  PStrBlobPtr() = default;
  PStrBlobPtr(StrBlobPtr& p) : p_(&p) {}
  StrBlobPtr& operator*() const;
  StrBlobPtr* operator->() const;

 private:
  StrBlobPtr* p_ = nullptr;
};

#endif /* ifndef PSTRBLOBPTR_H_ */
