#ifndef STR_H_
#define STR_H_

#include <cstddef>
#include <iostream>
#include <memory>
#include <utility>

class Str {
  friend std::ostream& operator<<(std::ostream&, const Str&);
  friend bool operator==(const Str&, const Str&);
  friend bool operator!=(const Str&, const Str&);

 public:
  Str();
  Str(const char*);
  Str(const int, const char);
  Str(const Str&);
  Str(Str&&) noexcept;
  Str& operator=(const Str&);
  Str& operator=(Str&&) noexcept;
  char& operator[](size_t n);
  const char& operator[](size_t n) const;
  ~Str();

  void push_back(char);
  void append(const char*);

  char* begin() const { return elements; }
  char* end() const { return first_free; }
  const char* c_str() const { return elements; }
  size_t size() const { return static_cast<size_t>(first_free - elements); }

 private:
  void chk_n_alloc() {
    if (size() == capacity()) {
      reallocate();
    }
  }
  std::pair<char*, char*> alloc_n_copy(const char*, const char*);
  void reallocate();
  void free();
  size_t capacity() const { return static_cast<size_t>(cap - elements); }

  static std::allocator<char> alloc;

  // 必须初始化三个指针
  // 否则初始化时无法正确计算size和capaticy
  char* elements = nullptr;
  char* first_free = nullptr;
  char* cap = nullptr;
};

std::ostream& operator<<(std::ostream&, const Str&);
bool operator==(const Str&, const Str&);
bool operator!=(const Str&, const Str&);

#endif
