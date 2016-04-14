#ifndef BLOGPTR_H_
#define BLOGPTR_H_

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "blob.h"

template <typename T>
class BlobPtr;

template <typename T>
bool operator==(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T>
bool operator!=(const BlobPtr<T>&, const BlobPtr<T>&);

template <typename T>
class BlobPtr {
  friend bool operator==<T>(const BlobPtr&, const BlobPtr&);
  friend bool operator!=<T>(const BlobPtr&, const BlobPtr&);

 public:
  BlobPtr() : curr_(0) {}
  BlobPtr(Blob<T>& a, std::size_t sz = 0) : wptr_(a.data_), curr_(sz) {}

  BlobPtr& operator++();
  BlobPtr& operator--();
  BlobPtr operator++(int);
  BlobPtr operator--(int);

  T& operator*() const {
    auto p = check(curr_, "dereference past end");
    return p->at(curr_);
  }
  T* operator->() const;

 private:
  std::shared_ptr<std::vector<T>> check(std::size_t, const std::string&) const;
  std::weak_ptr<std::vector<T>> wptr_;
  std::size_t curr_;
};

// public

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
  check(curr_, "increment past end");
  ++curr_;
  return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
  --curr_;
  check(curr_, "decrement past begining");
  return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
  BlobPtr ret = *this;
  ++*this;
  return ret;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
  BlobPtr ret = *this;
  --*this;
  return ret;
}

template <typename T>
std::shared_ptr<std::vector<T>> BlobPtr<T>::check(
    std::size_t sz, const std::string& msg) const {
  auto ret = wptr_.lock();

  if (!ret) {
    throw std::runtime_error("unbound BlobStr");
  }

  if (sz >= ret->size()) {
    throw std::out_of_range(msg);
  }

  return ret;
}

// friend

template <typename T>
bool operator==(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
  return lhs.curr_ == rhs.curr_;
}

template <typename T>
bool operator!=(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
  return !(lhs == rhs);
}

// function in Blob

template <typename T>
BlobPtr<T> Blob<T>::begin() {
  return BlobPtr<T>(*this);
}

template <typename T>
BlobPtr<T> Blob<T>::end() {
  return BlobPtr<T>(*this, data_->size());
}

#endif /* ifndef BLOGPTR_H_ */
