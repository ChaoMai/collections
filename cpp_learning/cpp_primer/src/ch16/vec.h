#ifndef VEC_H_
#define VEC_H_

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <utility>

template <typename T>
class Vec {
 public:
  Vec() : elements_(nullptr), first_free_(nullptr), cap_(nullptr) {}
  Vec(std::initializer_list<T>);
  Vec(const Vec&);
  Vec(Vec&&) noexcept;

  Vec& operator=(const Vec&);
  Vec& operator=(Vec&&) noexcept;

  ~Vec();

  void resize(std::size_t);
  void resize(std::size_t, const T&);
  void reserve(std::size_t);

  void push_back(const T&);
  void push_back(T&&);
  std::size_t size() const {
    return static_cast<std::size_t>(first_free_ - elements_);
  }
  std::size_t capacity() const {
    return static_cast<std::size_t>(cap_ - elements_);
  }
  T* begin() const { return elements_; }
  T* end() const { return first_free_; }

 private:
  void chk_n_alloc();
  std::pair<T*, T*> alloc_n_copy(const T*, const T*);
  void free();
  void reallocate();

  std::allocator<T> alloc_;
  T* elements_;
  T* first_free_;
  T* cap_;
};

// constructor and destructor

template <typename T>
Vec<T>::Vec(std::initializer_list<T> il) {
  auto newdata = alloc_n_copy(il.begin(), il.end());
  elements_ = newdata.first;
  first_free_ = cap_ = newdata.second;
}

template <typename T>
Vec<T>::Vec(const Vec& v) {
  auto newdata = alloc_n_copy(v.begin(), v.end());
  elements_ = newdata.first;
  first_free_ = cap_ = newdata.second;
}

// 移动操作不应抛出异常，p474
template <typename T>
Vec<T>::Vec(Vec&& v) noexcept : elements_(v.elements_),
                                first_free_(v.first_free_),
                                cap_(v.cap_) {
  v.elements_ = v.first_free_ = v.cap_ = nullptr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& rhs) {
  auto data = alloc_n_copy(rhs.begin(), rhs.end());

  free();

  elements_ = data.first;
  first_free_ = cap_ = data.second;

  return *this;
}

// 同上，不应抛出异常
template <typename T>
Vec<T>& Vec<T>::operator=(Vec&& rhs) noexcept {
  if (this != *rhs) {
    free();

    elements_ = rhs.elements_;
    first_free_ = rhs.first_free_;
    cap_ = rhs.cap_;

    rhs.elements_ = rhs.first_free_ = rhs.cap_ = nullptr;
  }
}

template <typename T>
Vec<T>::~Vec<T>() {
  free();
}

// public

template <typename T>
void Vec<T>::push_back(const T& ele) {
  chk_n_alloc();
  alloc_.construct(first_free_++, ele);
}

template <typename T>
void Vec<T>::push_back(T&& ele) {
  chk_n_alloc();
  alloc_.construct(first_free_++, std::move(ele));
}

// private

template <typename T>
void Vec<T>::chk_n_alloc() {
  if (size() == capacity()) {
    reallocate();
  }
}

template <typename T>
std::pair<T*, T*> Vec<T>::alloc_n_copy(const T* b, const T* e) {
  auto data = alloc_.allocate(static_cast<std::size_t>(e - b));
  return {data, std::uninitialized_copy(b, e, data)};
}

template <typename T>
void Vec<T>::free() {
  if (elements_) {
    // for (auto p = first_free_; p != elements_;) {
    // alloc_.destroy(--p);
    // }

    auto elem = elements_;
    for (std::size_t i = 0; i != size(); ++i) {
      alloc_.destroy(elem++);
    }

    alloc_.deallocate(elements_, capacity());
  }
}

template <typename T>
void Vec<T>::reallocate() {
  auto newcapacity = size() ? 2 * size() : 1;
  // auto newdata = alloc_.allocate(newcapacity);

  // auto dest = newdata;
  // auto elem = elements_;

  // for (std::size_t i = 0; i != size(); ++i) {
  // alloc_.construct(dest++, std::move(*elem++));
  // }

  // free();

  // elements_ = newdata;
  // first_free_ = dest;
  // cap_ = elements_ + newcapacity;

  auto first = alloc_.allocate(newcapacity);
  auto last =
      std::uninitialized_copy(std::make_move_iterator(elements_),
                              std::make_move_iterator(first_free_), first);

  free();

  elements_ = first;
  first_free_ = last;
  cap_ = elements_ + newcapacity;
}

#endif /* ifndef VEC_H_ */
