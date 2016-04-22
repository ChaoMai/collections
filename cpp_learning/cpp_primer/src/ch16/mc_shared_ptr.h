#ifndef MC_SHARED_PTR_H_
#define MC_SHARED_PTR_H_

#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>

#include "mc_unique_ptr.h"

template <typename T>
class McSharedPtr;

template <typename T>
void swap(McSharedPtr<T>&, McSharedPtr<T>&);

template <typename T>
class McSharedPtr {
  friend void swap<T>(McSharedPtr&, McSharedPtr&);

 public:
  using DeleterType = std::function<void(T*)>;

  McSharedPtr() : p_use_count_(new std::size_t(0)) {}
  // avoid implicit conversion
  explicit McSharedPtr(T*);
  McSharedPtr(McUniquePtr<T, DefaultDeleter>&);
  McSharedPtr(T*, DeleterType);
  McSharedPtr(const McSharedPtr&);
  McSharedPtr(const McSharedPtr&, DeleterType);
  // moving a function object is not noexcept
  // todo: any better solution?
  McSharedPtr(McSharedPtr&&);
  ~McSharedPtr();

  McSharedPtr& operator=(const McSharedPtr&);
  // moving a function object is not noexcept
  // todo: any better solution?
  McSharedPtr& operator=(McSharedPtr&&);
  T& operator*();
  T* operator->();

  bool unique() const { return use_count() == 1; }
  std::size_t use_count() const { return *p_use_count_; }
  T* get() const { return pt_; }
  void swap(McSharedPtr&);
  void reset();
  void reset(T*);
  void reset(T*, DeleterType);

  operator bool() const { return pt_ != nullptr; }

 private:
  void dec_and_delete();
  void set_empty(McSharedPtr&);

  T* pt_ = nullptr;
  std::function<void(T*)> pdf_;
  std::size_t* p_use_count_ = nullptr;
};

// constructor and destructor

template <typename T>
McSharedPtr<T>::McSharedPtr(T* pt) {
  pt_ = pt;
  p_use_count_ = new std::size_t(1);
}

template <typename T>
McSharedPtr<T>::McSharedPtr(McUniquePtr<T, DefaultDeleter>& mcuptr)
    : pt_(mcuptr.pt_),
      pdf_(DefaultDeleter()),
      p_use_count_(new std::size_t(1)) {
  mcuptr.reset();
}

template <typename T>
McSharedPtr<T>::McSharedPtr(T* pt, DeleterType deleter) {
  pt_ = pt;
  p_use_count_ = new std::size_t(1);
  pdf_ = deleter;
}

// it's constructor, so there is no left operand
template <typename T>
McSharedPtr<T>::McSharedPtr(const McSharedPtr& mcsptr)
    : pt_(mcsptr.pt_), pdf_(mcsptr.pdf_), p_use_count_(mcsptr.p_use_count_) {
  ++*p_use_count_;
}

template <typename T>
McSharedPtr<T>::McSharedPtr(const McSharedPtr& mcsptr, DeleterType deleter)
    : pt_(mcsptr.pt_), pdf_(deleter), p_use_count_(mcsptr.p_use_count_) {
  ++*p_use_count_;
}

template <typename T>
McSharedPtr<T>::McSharedPtr(McSharedPtr&& mcsptr)
    : pt_(mcsptr.pt_),
      pdf_(std::move(mcsptr.pdf_)),
      p_use_count_(mcsptr.p_use_count_) {
  set_empty(mcsptr);
}

template <typename T>
McSharedPtr<T>::~McSharedPtr<T>() {
  dec_and_delete();
}

// public member function

template <typename T>
McSharedPtr<T>& McSharedPtr<T>::operator=(const McSharedPtr& rhs) {
  ++*rhs.p_use_count_;
  dec_and_delete();

  pdf_ = rhs.pdf_;
  pt_ = rhs.pt_;
  p_use_count_ = rhs.p_use_count_;

  return *this;
}

template <typename T>
McSharedPtr<T>& McSharedPtr<T>::operator=(McSharedPtr&& rhs) {
  if (this != &rhs) {
    // this object is already changed,
    // so the position of move doesn't matter.
    // if copy throw an exception,
    // this object is always damaged.
    dec_and_delete();
    pt_ = rhs.pt_;
    pdf_ = std::move(rhs.pdf_);
    p_use_count_ = rhs.p_use_count_;

    set_empty(rhs);
  }
  return *this;
}

template <typename T>
T& McSharedPtr<T>::operator*() {
  return *pt_;
}

template <typename T>
T* McSharedPtr<T>::operator->() {
  return &this->operator*();
}

template <typename T>
inline void McSharedPtr<T>::swap(McSharedPtr& mcsptr) {
  using std::swap;
  swap(pt_, mcsptr.pt_);
  swap(pdf_, mcsptr.pdf_);
  swap(p_use_count_, mcsptr.p_use_count_);
}

template <typename T>
void McSharedPtr<T>::reset() {
  reset(nullptr, nullptr);
}

template <typename T>
// todo: avoid accept nullptr
void McSharedPtr<T>::reset(T* pt) {
  reset(pt, nullptr);
}

template <typename T>
// todo: avoid accept nullptr
void McSharedPtr<T>::reset(T* pt, DeleterType deleter) {
  dec_and_delete();
  pt_ = pt;
  pdf_ = deleter;
  p_use_count_ = new std::size_t(1);
}

// private member function

template <typename T>
void McSharedPtr<T>::dec_and_delete() {
  if (*p_use_count_ == 0) {
    delete p_use_count_;
  } else if (*p_use_count_ == 1) {
    pdf_ == nullptr ? delete pt_ : pdf_(pt_);
    delete p_use_count_;
  } else {
    --*p_use_count_;
  }
}

template <typename T>
void McSharedPtr<T>::set_empty(McSharedPtr& mcsptr) {
  mcsptr.pt_ = nullptr;
  mcsptr.pdf_ = nullptr;
  mcsptr.p_use_count_ = new std::size_t(0);
}

// friend function

template <typename T>
void swap(McSharedPtr<T>& lhs, McSharedPtr<T>& rhs) {
  using std::swap;
  swap(lhs.pt_, rhs.pt_);
  swap(lhs.pdf_, rhs.pdf_);
  swap(lhs.p_use_count_, rhs.p_use_count_);
}

// other function

// todo: forward parameter
template <typename T>
McSharedPtr<T> make_shared_McSharedPtr(T* pt) {
  return std::move(McSharedPtr<T>(pt));
}

#endif /* ifndef MC_SHARED_PTR_H_ */
