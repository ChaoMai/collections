#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <cstddef>
#include <string>

template <std::size_t H, std::size_t W>
class Screen;

template <std::size_t H, std::size_t W>
std::ostream &operator<<(std::ostream &, const Screen<H, W> &);

template <std::size_t H, std::size_t W>
std::istream &operator>>(std::istream &, Screen<H, W> &);

template <std::size_t H, std::size_t W>
class Screen {
  friend std::ostream &operator<<<H, W>(std::ostream &, const Screen &);
  friend std::istream &operator>><H, W>(std::istream &, Screen &);

 public:
  using pos = std::string::size_type;
  Screen() = default;
  Screen(pos num) : height_(H), width_(W), contents_(num, ' ') {}
  Screen(char c) : height_(H), width_(W), contents_(H * W, c) {}

  char get() const { return contents_[cursor_]; }
  char get(pos, pos) const;
  Screen &set(char);
  Screen &set(pos, pos, char);
  Screen &move(pos, pos);
  Screen &display(std::ostream &);
  const Screen &display(std::ostream &) const;

 private:
  void do_display(std::ostream &os) const { os << contents_; }

  pos cursor_ = 0;
  pos height_ = 0;
  pos width_ = 0;
  std::string contents_;
};

// public

template <std::size_t H, std::size_t W>
inline char Screen<H, W>::get(pos r, pos c) const {
  return contents_[r * width_ + c];
}

template <std::size_t H, std::size_t W>
inline Screen<H, W> &Screen<H, W>::set(char c) {
  contents_[cursor_] = c;
  return *this;
}

template <std::size_t H, std::size_t W>
inline Screen<H, W> &Screen<H, W>::set(pos r, pos c, char ch) {
  contents_[r * width_ + c] = ch;
  return *this;
}

template <std::size_t H, std::size_t W>
inline Screen<H, W> &Screen<H, W>::move(pos r, pos c) {
  cursor_ = r * width_ + c;
  return *this;
}

template <std::size_t H, std::size_t W>
inline Screen<H, W> &Screen<H, W>::display(std::ostream &os) {
  do_display(os);
  return *this;
}

template <std::size_t H, std::size_t W>
inline const Screen<H, W> &Screen<H, W>::display(std::ostream &os) const {
  do_display(os);
  return *this;
}

// friend

template <std::size_t H, std::size_t W>
std::ostream &operator<<(std::ostream &os, const Screen<H, W> &sc) {
  for (typename Screen<H, W>::pos i = 0; i < sc.height_; ++i) {
    // substr: pos and count
    os << sc.contents_.substr(i * sc.width_, sc.width_) << std::endl;
  }
  return os;
}

template <std::size_t H, std::size_t W>
std::istream &operator>>(std::istream &is, Screen<H, W> &sc) {
  char ch;
  is >> ch;
  std::string str(H * W, ch);
  sc.contents_ = str;
  return is;
}

#endif /* ifndef SCREEN_H_ */
