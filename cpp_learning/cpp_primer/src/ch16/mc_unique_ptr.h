#ifndef MC_UNIQUE_PTR_H_
#define MC_UNIQUE_PTR_H_

#include <cstddef>
#include <utility>

#include "default_deleter.h"

template <typename T, typename DeleterType>
class McUniquePtr;

template <typename T, typename DeleterType>
void swap(McUniquePtr<T, DeleterType>&, McUniquePtr<T, DeleterType>&);

template <typename T, typename DeleterType = DefaultDeleter>
class McUniquePtr {
  friend void swap<T, DeleterType>(McUniquePtr&, McUniquePtr&);

 public:
  McUniquePtr() = default;
  McUniquePtr(T*, DeleterType = DeleterType());
  McUniquePtr(DeleterType);
  McUniquePtr(const McUniquePtr&) = delete;
  // copy a deleter is not always noexcept
  McUniquePtr(McUniquePtr&&);
  ~McUniquePtr();

  McUniquePtr& operator=(const McUniquePtr&) = delete;
  // copy a deleter is not always noexcept
  McUniquePtr& operator=(McUniquePtr&&);
  T& operator*();
  T* operator->();

  T* get() const { return pt_; }
  void swap(McUniquePtr&);
  T* release();
  void reset();
  void reset(T*);

  operator bool() const { return pt_ != nullptr; }

 private:
  T* pt_ = nullptr;
  DeleterType pdf_;
};

// constructor and destructor

template <typename T, typename DeleterType>
McUniquePtr<T, DeleterType>::McUniquePtr(T* pt, DeleterType deleter)
    : pt_(pt), pdf_(deleter) {}

template <typename T, typename DeleterType>
McUniquePtr<T, DeleterType>::McUniquePtr(DeleterType deleter)
    : pdf_(deleter) {}

template <typename T, typename DeleterType>
McUniquePtr<T, DeleterType>::McUniquePtr(McUniquePtr&& mcuptr)
    : pt_(mcuptr.pt_), pdf_(mcuptr.pdf_) {
  mcuptr.pt_ = nullptr;
}

template <typename T, typename DeleterType>
McUniquePtr<T, DeleterType>::~McUniquePtr() {
  pdf_(pt_);
}

// public member function

template <typename T, typename DeleterType>
McUniquePtr<T, DeleterType>& McUniquePtr<T, DeleterType>::operator=(
    McUniquePtr&& rhs) {
  if (this != &rhs) {
    pt_ = rhs.pt_;
    pdf_ = std::move(rhs.pdf_);

    rhs.pt_ = nullptr;
  }
  return *this;
}

template <typename T, typename DeleterType>
T& McUniquePtr<T, DeleterType>::operator*() {
  return *pt_;
}

template <typename T, typename DeleterType>
T* McUniquePtr<T, DeleterType>::operator->() {
  return &this->operator*();
}

template <typename T, typename DeleterType>
void McUniquePtr<T, DeleterType>::swap(McUniquePtr& mcuptr) {
  using std::swap;
  swap(pt_, mcuptr, pt_);
  swap(pdf_, mcuptr, pdf_);
}

template <typename T, typename DeleterType>
T* McUniquePtr<T, DeleterType>::release() {
  auto ret = pt_;
  pdf_(pt_);
  pt_ = nullptr;
  return ret;
}

template <typename T, typename DeleterType>
void McUniquePtr<T, DeleterType>::reset() {
  reset(nullptr);
}

template <typename T, typename DeleterType>
void McUniquePtr<T, DeleterType>::reset(T* pt) {
  pdf_(pt_);
  pt_ = pt;
}

// friend function

template <typename T, typename DeleterType>
void swap(McUniquePtr<T, DeleterType>& lhs, McUniquePtr<T, DeleterType>& rhs) {
  using std::swap;
  swap(lhs.pt_, rhs.pt_);
  swap(lhs.pdf_, rhs.pdf_);
}

#endif /* ifndef MC_UNIQUE_PTR_H_ */
