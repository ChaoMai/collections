#include <algorithm>
#include <cstddef>
#include <cstring>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "blob.h"
#include "blobptr.h"
#include "debug_delete.h"
#include "mc_shared_ptr.h"
#include "mc_unique_ptr.h"
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
using std::make_shared;
using std::max;
using std::ostringstream;
using std::remove_reference;
using std::shared_ptr;
using std::size_t;
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
int compare_literal(const char (&p1)[N], const char (&p2)[M]) {
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
void print_array(const T (&arr)[N]) {
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
T *arr_begin(T (&arr)[N]) {
  return static_cast<T *>(arr);
}

// 形参和返回值都不能是const
template <typename T, size_t N>
T *arr_end(T (&arr)[N]) {
  return static_cast<T *>(arr + N);
}

void t6() {
  int arr[] = {1, 2, 2, 3, 5, 6, 7, 8, 5, 34};
  cout << *arr_begin(arr) << endl;
  cout << *(arr_end(arr) - 1) << endl;
}

// 返回值必须指定constexpr
template <typename T, size_t N>
constexpr size_t constexpr_arr_size(T (&arr)[N]) {
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

void t17() {
  vector<string> vs{"awef", "qwer", "zxcv"};
  Blob<string> b(vs.begin(), vs.end());
}

template <typename T>
class F;

template <typename T>
void pf3(F<T>);

template <typename T>
class F {
  friend void pf(T);
  friend void pf1(F);
  friend void pf2(F);
  friend void pf3<T>(F);

 public:
  F() = default;

 private:
  T t = 100;
};

template <typename T>
void pf(T f) {
  cout << f.t << endl;
}

template <typename T>
void pf1(F<T> f) {
  cout << f.t << endl;
}

void pf2(F<int> f) { cout << f.t << endl; }

template <typename T>
void pf3(F<T> f) {
  cout << f.t << endl;
}

void t18() {
  F<int> f;
  // pf(f); // cannot access
  // pf1(f); // cannot access
  // pf1<int>(f); // cannot access
  // pf2(f); // ok
  pf3(f);
}

template <typename T>
class NoDefault {
 public:
  NoDefault(int a) {}
};

template class NoDefault<int>;  // ok
// template class std::vector<NoDefault<int>>;  // error
template class std::vector<int>;  // ok

void t19() { NoDefault<int> nd(1); }

// template <typename T>
// class Stack;

// void f1(Stack<char>);

// class Exerciese {
// // Exerciese():rsd(Stack<double>()){}
// Stack<double>&rsd;
// Stack<int>si;
// };

// void t20() {
// Stack<char> *sc;
// f1(*sc);
// int iObj = sizeof(Stack<string>);
// }

void t21() {
  function<void()> f;
  cout << (f == nullptr) << endl;

  shared_ptr<int> pi;
  cout << pi.use_count() << endl;

  shared_ptr<double> pd(new double(2.0));
  // cannot reset to nullptr
  pd.reset(new double(10.), [](double *p) {
    cout << "delete pd" << endl;
    delete p;
  });

  pd.reset(static_cast<double *>(nullptr));
  cout << pd.use_count() << endl;
}

void t22() {
  McSharedPtr<double> pd;
  cout << pd.use_count() << endl;

  McSharedPtr<int> pi(new int(100));
  cout << *pi << endl;

  McSharedPtr<string> ps(new string("chaomai,c"));
  auto psc(ps);
  cout << *psc << endl;
  cout << psc.use_count() << endl;

  McSharedPtr<string> ps1(new string("chaomai,m"));
  auto psm(std::move(ps1));
  cout << *psm << endl;
  cout << psm.use_count() << endl;
  cout << ps1.use_count() << endl;

  cout << "---" << endl;

  McSharedPtr<string> ps2(new string("chaomai,c"));
  McSharedPtr<string> psc1;
  psc1 = ps2;
  cout << *psc1 << endl;
  cout << psc1.use_count() << endl;
  cout << ps2.use_count() << endl;

  psc1 = psc1;
  cout << psc1.use_count() << endl;

  McSharedPtr<string> ps3(new string("chaomai,m"));
  McSharedPtr<string> psm1;
  psm1 = std::move(ps3);

  cout << *psm1 << endl;
  cout << psm1.use_count() << endl;
  cout << ps3.use_count() << endl;

  psm1 = std::move(psm1);
  cout << *psm1 << endl;
  cout << psm1.use_count() << endl;

  cout << "---" << endl;

  McSharedPtr<string> ps4(new string("chaomai,d"), [](string *p) {
    cout << "ps4 customized deleter" << endl;
    delete p;
  });

  cout << "---" << endl;

  McSharedPtr<string> ps5(new string("chaomai,b"));
  if (ps5) {
    cout << "has data" << endl;
  }
  ps5.reset(nullptr, [](string *p) {
    cout << "ps5 customized deleter" << endl;
    delete p;
  });
  cout << ps5.use_count() << endl;
}

void t23() {
  unique_ptr<int> pi(new int(1));
  // unique_ptr<int>pi1(pi);
  unique_ptr<int> pi1(std::move(pi));

  unique_ptr<int> pi2;
  // pi2 = pi1;
  pi2 = std::move(pi1);
}

void t24() {
  McUniquePtr<int> pi(new int(1));
  cout << *pi << endl;

  cout << "---" << endl;

  McUniquePtr<string> ps(new string("maichao,m"));
  cout << *ps << endl;

  McUniquePtr<string> ps1(std::move(ps));
  cout << *ps1 << endl;
  cout << (ps.get() == nullptr) << endl;

  McUniquePtr<string> ps2(McUniquePtr<string>(new string("maichao,t")));
  cout << *ps2 << endl;

  McUniquePtr<string> ps3;
  ps3 = std::move(ps2);
  ps3 = McUniquePtr<string>(new string("maichao,t1"));
  cout << *ps3 << endl;
  cout << ps3->size() << endl;

  McUniquePtr<string, function<void(string *)>> ps4([](string *p) {
    cout << "called deleter" << endl;
    delete p;
  });

  McUniquePtr<string, function<void(string *)>> ps5(new string("maichao,db"),
                                                    DebugDelete());
}

template <typename T>
T fobj(T, T) {}

template <typename T>
T fref(const T &, const T &) {}

template <typename T>
T &fref2(const T &a, const T &) {}

void t25() {
  int a[10];
  int b[42];
  fobj(a, b);  // ok, fobj(int*, int*)
  // fref(a, b);  // 错误
  // fref2(a, b);  // 错误

  int c[10];
  // fref(a, c);
  fref2(a, c);
}

template <typename T1, typename T2, typename T3>
T1 sum(T2, T3) {}

void t26() {
  auto val = sum<long>(1, 10);
  long l = 10;
  max<long>(l, 100);
  compare<char const *>("huhuawef", "awef");
}

template <typename It>
auto fcn(It beg, It end) -> decltype(*beg) {
  return *beg;
}

template <typename It>
auto fcn2(It beg, It end) -> typename remove_reference<decltype(*beg)>::type {
  return *beg;
}

void t27() {
  int i = 10;
  (i) = 20;
  cout << i << endl;

  vector<int> vi{1, 2, 3};
  fcn(vi.begin(), vi.end()) = 10;
  cout << fcn2(vi.begin(), vi.end()) << endl;
}

template <typename T>
int comp(const T &, const T &) {
  return 100;
}

int funcomp(int (*)(const int &, const int &)) { return 0; }
int funcomp(int (*)(const string &, const string &)) { return 0; }

void t28() {
  int (*pf1)(const int &, const int &) = comp;
  cout << pf1(1, 1) << endl;
  funcomp(comp<int>);
}

template <typename T>
void f1(T &) {}

template <typename T>
void f2(const T &) {}

template <typename T>
void f3(T &&) {}

template <typename T>
void ff3(T) {}

void fun3(int &&) {}

void t29() {
  int i = 10;
  const int ci = 20;
  f3(i);
  // f3(ci);
  // fun3(i);
  // fun3(ci);

  using l = int &;
  using ll = l &;
  using r = int &&;
  using lr = l &&;
  using rr = r &&;
  using rrr = rr &&;
  using rrrr = rrr &&;

  l li = i;
  r ri = 20;
  rr rri = 20;
  rrr rrri = 20;
  rrrr rrrri = 20;

  f3(li);

  f3(ri);
  f3(rri);
  f3(rrri);
  f3(rrrri);

  f3(20);
  f3(std::move(li));

  ff3(i);
  ff3(ci);
  ff3(i * ci);
}

void t30() {
  int &&ri = 20;
  cout << &ri << endl;

  int i = 10;
  int &&ri1 = static_cast<int &&>(i);
}

template <typename F, typename T1, typename T2>
void flip1(F f, T1 &&t1, T2 &&t2) {
  f(t1, t2);
}

template <typename F, typename T1, typename T2>
void flip2(F f, T1 &&t1, T2 &&t2) {
  f(std::forward<T1>(t1), std::forward<T2>(t2));
}

void ff1(int v1, int v2) {}

void ff2(int &&v1, int v2) {}

void t31() {
  int v1 = 1;
  int v2 = 5;

  flip1(ff1, v1, v2);
  flip2(ff1, v1, v2);

  // flip1(ff2, 10, v2);
  flip2(ff2, 10, v2);
}

template <typename T>
string debug_rep(T const &t) {
  ostringstream ret;
  ret << t;
  return ret.str();
}

template <typename T>
string debug_rep(T *p) {
  ostringstream ret;
  ret << "pointer: " << p;

  if (p) {
    ret << " " << debug_rep(*p);
  } else {
    ret << " null pointer";
  }

  return ret.str();
}

void t32() {
  string s("maichao");
  cout << debug_rep(s) << endl;
  cout << debug_rep(&s) << endl;

  string *ps = &s;
  string const *cps = &s;
  // string const *&t = &s; // error
  string *&t = ps;
  // string const *const &t = &s;
  // string const *&rps = ps; // error
}

template <typename T, size_t N>
T *arr_b(T (&arr)[N]) {
  return arr;
}

template <typename T, size_t N>
T *arr_e(T (&arr)[N]) {
  return arr + N;
}

template <typename T, size_t N>
size_t arr_s(T (&arr)[N]) {
  return N;
}

void t33() {
  int a[5] = {1, 2, 3, 4, 50};

  cout << *arr_b(a) << endl;
  cout << *(arr_e(a) - 1) << endl;
  cout << arr_s(a) << endl;
}

template <typename T>
void forward_test(T &&t) {
  t = 100;
}

void t34() {
  int i = 10;
  int &ri = i;

  forward_test(ri);
  cout << i << endl;
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
  // t16();
  // t17();
  // t18();
  // t19();
  // t20();
  // t21();
  // t22();
  // t23();
  // t24();
  // t25();
  // t26();
  // t27();
  // t28();
  // t29();
  // t30();
  // t31();
  // t32();
  // t33();
  t34();
  return 0;
}
