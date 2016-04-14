#ifndef BLOB_H_
#define BLOB_H_

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class BlobPtr;

template <typename T>
class Blob;

template <typename T>
bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T>
bool operator!=(const Blob<T>&, const Blob<T>&);

template <typename T>
class Blob {
  friend class BlobPtr<T>;
  // 这里必须有<T>
  friend bool operator==<T>(const Blob&, const Blob&);
  friend bool operator!=<T>(const Blob&, const Blob&);

 public:
  using value_type = T;
  using size_type = typename std::vector<T>::size_type;

  Blob();
  Blob(std::initializer_list<T>);
  Blob(const Blob&);
  Blob& operator=(const Blob&);

  size_type size() const { return data_->size(); }
  bool empty() const { return data_->empty(); }

  void push_back(const T& t) { data_->push_back(t); }
  void push_back(T&& t) { data_->push_back(std::move(t)); }
  void pop_back();

  T& front();
  T& front() const;
  T& back();
  T& back() const;
  BlobPtr<T> begin();
  BlobPtr<T> end();

  T& operator[](size_type i);
  const T& operator[](size_type i) const;

 private:
  std::shared_ptr<std::vector<T>> data_;
  void check(size_type i, const std::string& msg) const;
};

// constructor

template <typename T>
Blob<T>::Blob()
    : data_(std::make_shared<std::vector<T>>()) {}

template <typename T>
Blob<T>::Blob(std::initializer_list<T> il)
    : data_(std::make_shared<std::vector<T>>(il)) {}

template <typename T>
void Blob<T>::pop_back() {
  check(0, "pop_back on empty Blob");
  data_->pop_back();
}

template <typename T>
Blob<T>::Blob(const Blob& rhs)
    : data_(std::make_shared<std::vector<T>>(*rhs.data_)) {}

template <typename T>
Blob<T>& Blob<T>::operator=(const Blob& rhs) {
  data_ = std::make_shared<std::vector<T>>(*rhs.data_);
  return *this;
}

// public

template <typename T>
T& Blob<T>::front() {
  check(0, "front on empty Blob");
  return data_->front();
}

template <typename T>
T& Blob<T>::front() const {
  check(0, "front on empty Blob");
  return data_->front();
}

template <typename T>
T& Blob<T>::back() {
  check(0, "back on empty Blob");
  return data_->back();
}

template <typename T>
T& Blob<T>::back() const {
  check(0, "back on empty Blob");
  return data_->back();
}

template <typename T>
T& Blob<T>::operator[](size_type i) {
  check(i, "subscript out of range");
  return data_->at(i);
}

template <typename T>
const T& Blob<T>::operator[](size_type i) const {
  check(i, "subscript out of range");
  return data_->at(i);
}

template <typename T>
void Blob<T>::check(size_type i, const std::string& msg) const {
  if (i >= data_->size()) {
    throw std::out_of_range(msg);
  }
}

// friend

template <typename T>
bool operator==(const Blob<T>& lhs, const Blob<T>& rhs) {
  return *lhs.data_ == *rhs.data_;
}

template <typename T>
bool operator!=(const Blob<T>& lhs, const Blob<T>& rhs) {
  return !(lhs == rhs);
}

#endif /* ifndef BLOB_H_ */
