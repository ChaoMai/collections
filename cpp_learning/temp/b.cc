template <typename T>
T fobj(T, T) {}

template <typename T>
T fref(const T &, const T &) {}

template <typename T>
T &fref2(const T &, const T &) {}

int(&f(int(&)[10], int(&)[10]))[10];

int main() {
  int a[10];
  int b[42];
  fobj(a, b);  // ok, fobj(int*, int*)
  // fref(a, b);  // 错误
  // fref2(a, b);  // 错误

  int c[10];
  // fref(a, c);
  fref2(a, c);
}
