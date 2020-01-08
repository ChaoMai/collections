#include "pstrblobptr.h"

StrBlobPtr& PStrBlobPtr::operator*() const { return *(this->p_); }

StrBlobPtr* PStrBlobPtr::operator->() const { return &this->operator*(); }
