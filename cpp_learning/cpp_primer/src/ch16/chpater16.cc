#include <algorithm>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "blob.h"
#include "blobptr.h"
#include "debug_delete.h"
#include "sales_data.h"
#include "screen.h"
#include "vec.h"

using std::cin;
using std::cout;
using std::endl;
using std::for_each;
using std::function;
using std::greater;
using std::less;
using std::string;
using std::unique_ptr;
using std::vector;

template <typename T>
int compare(const T &v1, const T &v2) {
  if (v1 < v2) {
    return -1;
  }

  if (v2 < v1) {
    return 1;
  }

  return 0;
}

void t1() {
  cout << compare(123, 234) << endl;
  cout << compare("asdf", "qwer") << endl;
  cout << compare("qwer", "asdf") << endl;
  cout << compare("qwer", "qwer") << endl;
  cout << compare(string("asdf"), string("qwer")) << endl;
  cout << compare(string("qwer"), string("asdf")) << endl;
  cout << compare(string("qwer"), string("qwer")) << endl;

  Sales_data sd1;
  Sales_data sd2;

  // cout << compare(sd1, sd2) << endl;
}

void t2() {
  const char *s1 = "asdf";
  const char *s2 = "qwer";
  cout << compare(s1, s2) << endl;
  cout << compare(s2, s1) << endl;
  cout << compare(s2, s2) << endl;
}

template <unsigned N, unsigned M>
int compare_literal(const char(&p1)[N], const char(&p2)[M]) {
  cout << "strcmp" << endl;
  return strcmp(p1, p2);
}

void t3() {
  cout << compare_literal("asdf", "qwer") << endl;
  cout << compare_literal("qwer", "asdf") << endl;
  cout << compare_literal("qwer", "qwer") << endl;
}

template <typename Iter, typename Value>
Iter find_value(Iter beg, Iter end, const Value &v) {
  while (beg != end) {
    if (*beg == v) {
      break;
    } else {
      ++beg;
    }
  }

  return beg;
}

void t4() {
  vector<int> vi{12, 3, 4, 5, 5};
  cout << (find_value(vi.begin(), vi.end(), 5) == vi.end()) << endl;
  cout << *find_value(vi.begin(), vi.end(), 5) << endl;
  cout << (find_value(vi.begin(), vi.end(), 10) == vi.end()) << endl;
}

template <typename T, size_t N>
void print_array(const T(&arr)[N]) {
  for (size_t i = 0; i < N; ++i) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

template <typename T>
void print_array_range_for(const T &arr) {
  for (auto i : arr) {
    cout << i << " ";
  }
  cout << endl;
}

void t5() {
  int arr[] = {1, 2, 2, 3, 5, 6, 7, 8, 5, 34, 3};
  print_array(arr);
  print_array_range_for(arr);

  Sales_data sds[10];
  print_array(sds);
  print_array_range_for(sds);
}

template <typename T, size_t N>
T *arr_begin(T(&arr)[N]) {
  return static_cast<T *>(arr);
}

// 形参和返回值都不能是const
template <typename T, size_t N>
T *arr_end(T(&arr)[N]) {
  return static_cast<T *>(arr + N);
}

void t6() {
  int arr[] = {1, 2, 2, 3, 5, 6, 7, 8, 5, 34};
  cout << *arr_begin(arr) << endl;
  cout << *(arr_end(arr) - 1) << endl;
}

// 返回值必须指定constexpr
template <typename T, size_t N>
constexpr size_t constexpr_arr_size(T(&arr)[N]) {
  return N;
}

void t7() {
  int arr[] = {1, 2, 2, 3, 5, 6, 7, 8, 5, 34};
  constexpr int size = constexpr_arr_size(arr);
  cout << size << endl;

  // int arr2[constexpr_arr_size(arr) + constexpr_arr_size(arr)];
  // cout << constexpr_arr_size(arr2) << endl;
}

template <typename T>
class Foo {
 public:
  static size_t count() { return ++ctr; }

  static size_t ctr;
};

template <typename T>
size_t Foo<T>::ctr = 0;

void t8() {
  Foo<int> f1, f2, f3;
  f1.count();
  f2.count();
  f3.count();
  cout << f1.ctr << endl;

  Foo<string> s1, s2;
  s1.count();
  s2.count();
  cout << s1.ctr << endl;

  cout << Foo<double>::count() << endl;
}

void t9() {
  Blob<string> b1;
  b1.push_back("awef");
  b1.push_back("zxcv");

  Blob<string> b2;
  b2.push_back("poiu");
  b2.push_back("lkjh");

  Blob<string> b3 = b2;

  cout << (b1 == b2) << endl;
  cout << (b2 == b3) << endl;
}

void t10() {
  Blob<string> b1;
  b1.push_back("awef");
  b1.push_back("zxcv");
  b1.push_back("poiu");
  b1.push_back("lkjh");
  b1.push_back("mnbv");

  BlobPtr<string> bp1(b1);
  cout << *(bp1++) << endl;
  cout << *(bp1++) << endl;
  cout << *(bp1++) << endl;
  cout << *(bp1++) << endl;
  cout << *(bp1++) << endl;

  // past end
  // cout << *(bp1++) << endl;
}

void t11() {
  Screen<10, 5> sc('a');
  cout << sc << endl;

  cin >> sc;
  cout << sc << endl;
}

void t12() {
  Vec<int> vi{1, 2, 3, 4, 5};
  for_each(vi.begin(), vi.end(), [](int i) { cout << i << " "; });
  cout << endl;

  Vec<string> vs;
  vs.push_back("awef");
  vs.push_back("bwef");
  vs.push_back("cwef");
  for_each(vs.begin(), vs.end(), [](const string &s) { cout << s << " "; });
  cout << endl;

  Vec<Sales_data> vsd{Sales_data(), Sales_data(), Sales_data()};
  for_each(vsd.begin(), vsd.end(),
           [](const Sales_data &s) { cout << s << " "; });
  cout << endl;
}

template <typename T>
class C;

template <typename T>
void func(C<T> &);

template <typename T>
class C {
  friend void func<T>(C &);

 public:
 private:
  int c = 10;
};

template <typename T>
void func(C<T> &c) {
  cout << c.c << endl;
}

void t13() {
  C<int> c;
  func(c);
}

template <typename T, typename F = less<T>>
int compare_default(const T &v1, const T &v2, F f = F()) {
  if (f(v1, v2)) {
    return -1;
  }

  if (f(v2, v1)) {
    return 1;
  }

  return 0;
}

void t14() {
  cout << greater<int>()(1, 4) << endl;
  cout << compare_default(1, 4, greater<int>()) << endl;
  cout << compare_default<int, greater<int>>(1, 4) << endl;
  // cout << compare_default<int, bool (*)(int, int)>(1, 4) << endl;
  // core dump
  // cout << compare_default<int, function<bool(int, int)>>(1, 4) << endl;
  // terminate called after throwing an instance of 'std::bad_function_call
  cout << compare_default<int, bool (*)(int, int)>(1, 4, [](int, int) {
    return true;
  }) << endl;
}

template <typename T>
void print_container(const T &c) {
  for (typename T::size_type i = 0; i != c.size(); ++i) {
    cout << c[i] << " ";
  }
  cout << endl;
}

template <typename T>
void print_container2(const T &c) {
  // const auto won't work, as the `const auto it` is
  //`const typename T::const_iterator it`
  // for (typename T::const_iterator it = c.cbegin(); it != c.cend(); ++it) {
  for (auto it = c.cbegin(); it != c.cend(); ++it) {
    cout << *it << " ";
  }
  cout << endl;
}

void t15() {
  vector<int> vi{1, 2, 3, 4, 5, 6, 7, 8, 9};
  print_container(vi);
  print_container2(vi);
}

void t16() {
  double *pd = new double(10);
  DebugDelete d;
  d(pd);

  unique_ptr<vector<string>, DebugDelete> upv(new vector<string>,
                                              DebugDelete());
  upv->push_back("awef");
  upv->push_back("awef");
  upv->push_back("awef");
  upv->push_back("awef");
  upv->push_back("awef");

  unique_ptr<int, function<void(int *)>> up(
      new int(10), [](int *) { cout << "called" << endl; });
}

template <typename T>
void ff(T t) {
  cout << t << endl;
}

template <typename T>
class F {
  template <typename FT>
  friend void ff(FT);

 public:
  F() = default;

 private:
  T t = 0;
};

void t17() {
  vector<string> vs{"awef", "qwer", "zxcv"};
  Blob<string> b(vs.begin(), vs.end());
}

int main(int argc, char *argv[]) {
  // t1();
  // t2();
  // t3();
  // t4();
  // t5();
  // t6();
  // t7();
  // t8();
  // t9();
  // t10();
  // t11();
  // t12();
  // t13();
  // t14();
  // t15();
  t16();
  return 0;
}
