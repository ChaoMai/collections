#include <algorithm>
#include <array>
#include <chrono>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "c.h"
#include "folder.h"
#include "hasptr.h"
#include "hasptr1.h"
#include "hasptr2.h"
#include "hasptr3.h"
#include "hasptr_ptr.h"
#include "hasptr_value.h"
#include "message.h"
#include "str.h"
#include "strvec.h"

using std::allocator;
using std::array;
using std::cin;
using std::cout;
using std::endl;
using std::for_each;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;
using std::initializer_list;
using std::make_shared;
using std::out_of_range;
using std::pair;
using std::runtime_error;
using std::set;
using std::shared_ptr;
using std::sort;
using std::string;
using std::uninitialized_copy;
using std::vector;
using std::weak_ptr;

void t1() {
  HasPtr a("abc");
  a.arr[0] = 232;
  a.arr[1] = 232;
  a.sarr[0] = 232;
  a.sarr[1] = 232;

  HasPtr b = a;
  HasPtr c;
  c = a;
  (*b.ps).append("a");
  cout << *a.ps << " " << *b.ps << " " << *c.ps << endl;
  cout << a.arr[0] << " " << b.arr[0] << " " << b.sarr[0] << endl;
  cout << a.sarr[0] << " " << c.arr[0] << " " << c.sarr[0] << endl;
}

void f(C c) {
  C tmp;
  tmp = c;
}

C f() { return C(); }

void fr(C &c) {
  C tmp(0);
  tmp = c;
}

void f(initializer_list<C> il) {
  C tmp(0);
  tmp = *il.begin();
}

void t2() {
  C c1(1);
  C c2(c1);
  C c3(3);
  c3 = c1;
  cout << "-----" << endl;

  f(c1);
  cout << "-----" << endl;
  f(C(2));
  cout << "-----" << endl;

  C c = f();
  cout << "-----" << endl;

  fr(c1);
  // fr(C(4));
  cout << "-----" << endl;

  f({c1});
  f({C()});
  cout << "-----" << endl;

  vector<C> vc{C()};
  vector<C> vc1{c3};

  // avoid extra copy of elements
  vc1.reserve(16);
  vc1.emplace_back(5);
  vc1.push_back(c1);
  cout << "-----" << endl;

  auto p = shared_ptr<C>(make_shared<C>(6));

  int a;
  cin >> a;
}

void t3() {
  // auto p = &C(1);
  // C &c = C(2);
  const C &c = C(2);
  // cout << p << endl;
}

int count = 0;

class numbered {
 public:
  numbered() : mysn(++count) {}
  numbered(const numbered &rhs) : mysn(++count) { cout << "copyed" << endl; }
  int mysn;
};

void f1(const numbered &s) { cout << s.mysn << endl; }

void t4() {
  numbered a, b = a, c = b;
  f1(a);
  f1(b);
  f1(c);
}

class Employee {
 public:
  Employee() : id_(++id_count){};
  Employee(const string &name) : name_(name), id_(++id_count) {}
  Employee(const Employee &rhs) : name_(rhs.name_), id_(++id_count) {}
  Employee &operator=(const Employee &rhs) {
    name_ = rhs.name_;
    id_ = ++id_count;
    return *this;
  }
  string name_;
  int id_;
  static int id_count;
};

int Employee::id_count = 0;

void t5() {
  Employee e1("awef");
  Employee e2 = e1;
  Employee e3("waeff");
  Employee e4;
  // cout << e4.name_ << " " << e4.id_ << endl;
  e4 = e3;
  cout << e1.name_ << " " << e1.id_ << endl;
  cout << e2.name_ << " " << e2.id_ << endl;
  cout << e3.name_ << " " << e3.id_ << endl;
  cout << e4.name_ << " " << e4.id_ << endl;
}

class TreeNode {
 public:
  TreeNode(const string &v = string(), TreeNode *l = nullptr,
           TreeNode *r = nullptr)
      : value(v), count(new int(1)), left(l), right(r) {}
  TreeNode(const TreeNode &rhs)
      : value(rhs.value), count(rhs.count), left(nullptr), right(nullptr) {
    ++*count;
  }
  TreeNode &operator=(const TreeNode &rhs) {
    ++*rhs.count;
    if (--*count == 0) {
      delete count;
      if (left) {
        delete left;
      }
      if (right) {
        delete right;
      }
    }
    count = rhs.count;
    left = rhs.left;
    right = rhs.right;
    return *this;
  }
  ~TreeNode() {
    if (--*count == 0) {
      delete count;
      if (left) {
        delete left;
      }
      if (right) {
        delete right;
      }
    }
  }

 private:
  string value;
  int *count;
  TreeNode *left;
  TreeNode *right;
};

class BinStrTree {
 public:
  BinStrTree() : root(new TreeNode()) {}
  // will call the copy constructor of TreeNode
  BinStrTree(const BinStrTree &rhs) : root(new TreeNode(*rhs.root)) {}
  BinStrTree &operator=(const BinStrTree &rhs) {
    auto newr = new TreeNode(*rhs.root);
    delete root;
    root = newr;
    return *this;
  }
  ~BinStrTree() { delete root; }

 private:
  TreeNode *root;
};

void t6() {
  // vector<HasPtr1> vh{HasPtr1("wafe"),    HasPtr1("xcvxz"), HasPtr1("iojoi"),
  // HasPtr1("qfe,mnj"), HasPtr1("absa"),    HasPtr1("wafe"),
  // HasPtr1("xcvxz"),   HasPtr1("iojoi"),   HasPtr1("qfe,mnj"),
  // HasPtr1("absa"),    HasPtr1("wafe"),    HasPtr1("xcvxz"),
  // HasPtr1("iojoi"),   HasPtr1("qfe,mnj"), HasPtr1("absa"),
  // HasPtr1("wafe"),    HasPtr1("xcvxz"),   HasPtr1("iojoi"),
  // HasPtr1("qfe,mnj")};
  vector<HasPtr1> vh{HasPtr1("wafe"),    HasPtr1("xcvxz"), HasPtr1("iojoi"),
                     HasPtr1("qfe,mnj"), HasPtr1("absa"),  HasPtr1("wafe"),
                     HasPtr1("xcvxz"),   HasPtr1("iojoi"), HasPtr1("qfe,mnj"),
                     HasPtr1("qfe,mnj")};
  cout << vh.size() << endl;
  sort(vh.begin(), vh.end());
  // for (auto &h : vh) {
  // cout << h.getStr() << endl;
  // }
}

void t7() {
  double dval = 3.14;
  const int &ri = dval;
  cout << ri << endl;
  dval = 31.4;
  cout << ri << endl;
}

void t8() {
  Folder f1;
  Folder f2;

  Message m1("1");
  Message m2("2");
  Message m3("3");
  Message m4("4");
  Message m5("5");
  Message m6("6");

  m1.save(f1);
  m2.save(f1);
  m3.save(f1);
  m4.save(f2);
  m5.save(f2);
  m6.save(f1);
  m6.save(f2);

  listFolder(f1);
  listFolder(f2);

  // Folder f3;
  // listFolder(f3);
  // f3 = f1;
  // listFolder(f3);

  // Folder f4(f2);
  // listFolder(f3);

  listContainingFolders(m1);
  listContainingFolders(m6);
  swap(f1, f2);
  // listFolder(f1);
  // listFolder(f2);
  // listFolder(f3);
  // listFolder(f4);
  listContainingFolders(m1);
  listContainingFolders(m6);
}

void t9() {
  StrVec sv{"a", "b", "c", "d", "e"};
  for (auto &s : sv) {
    cout << s << endl;
  }
}

void t10() {
  string sarr[]{"wsa", "waf"};
  for_each(begin(sarr), end(sarr), [](string &s) { cout << s << endl; });
}

void foo(Str x) { cout << x.c_str() << endl; }

void bar(const Str &x) { cout << x.c_str() << endl; }

Str baz() {
  Str ret("world");
  return ret;
}

void t11() {
  char text[] = "world";

  Str s0;
  Str s1("hello");
  Str s2(s0);
  Str s3 = s1;
  Str s4(text);
  s2 = s1;

  cout << s0.c_str() << endl;
  cout << s1.c_str() << endl;
  cout << s2.c_str() << endl;
  cout << s3.c_str() << endl;
  cout << s4.c_str() << endl;

  foo(s1);
  bar(s1);
  foo("temporary");
  bar("temporary");
  Str s5 = baz();

  vector<Str> svec;
  svec.reserve(8);
  svec.push_back(s0);
  svec.push_back(s1);
  svec.push_back(s2);
  svec.push_back(s3);
  svec.push_back(s4);
  svec.push_back(s5);
  svec.push_back(baz());
  svec.push_back("good job");

  for (const auto &s : svec) {
    cout << s.c_str() << endl;
  }
}

void t12() {
  int i = 5;
  int &&rri = static_cast<int &&>(i);
  int &&rri1 = std::move(i);
  // int &&rri2 = i;
  int &r = rri;
  i = 10;
  ++r;
  cout << i << endl;
  cout << rri << endl;
  cout << rri1 << endl;
  cout << r << endl;

  double d = 3.14;
  int &&rrd = std::move(d);
  d *= 10;
  cout << rrd << endl;

  int &&rrd1 = std::move(rrd);
  ++rrd;
  cout << rrd << endl;
  cout << rrd1 << endl;
}

void t13() {
  Str str;
  str.push_back('1');
  str.push_back('2');
  str.push_back('3');
  str.append("12345");

  vector<Str> vs;
  vs.reserve(10);
  vs.push_back(Str("awf"));
  vs.push_back(Str("awf"));
  vs.push_back(Str("awf"));
  vs.push_back(str);

  for (const auto &s : vs) {
    cout << s.c_str() << endl;
  }
}

class T {
 public:
  T() = default;
  T(T &&t) noexcept { throw runtime_error("error"); }
};

struct X {
  int i;
  string s;
};

struct hasX {
  X mem;
};

struct Y {
  Y(const Y &y) {}
  int i;
  string s;
};

struct hasY {
  hasY() = default;
  hasY(hasY &&) = default;
  Y mem;
};

class Foo {
 public:
  Foo() = default;
  Foo(const Foo &) { cout << "copied" << endl; }
};

void t14() {
  // T t;
  // T t1(std::move(t));

  X x, x2 = std::move(x);
  hasX hx, hx2 = std::move(hx);

  // hasY hy, hy2 = std::move(hy);

  Foo foo;
  Foo foo1(foo);
  Foo foo2(std::move(foo1));
}

class Hp {
 public:
  Hp() = default;
  Hp(const Hp &) { cout << "copied" << endl; }
  Hp(Hp &&) { cout << "moved" << endl; }
  Hp &operator=(Hp rhs) {
    cout << "assign" << endl;
    return *this;
  }
};

void t15() {
  Hp hp1;
  Hp hp2 = hp1;
  Hp hp3 = std::move(hp1);

  cout << "---" << endl;

  hp1 = hp3;
  hp2 = std::move(hp3);
}

Str fun() { return Str("in func"); }

void t16() {
  // Str str = std::move(fun());
  // Str str = fun();
  // cout << str.c_str() << endl;

  // 如果没有rvo，这里会有一次move
  cout << fun().c_str() << endl;
}

void t17() {
  HasPtr3 hp;
  HasPtr3 hp1;
  HasPtr3 hp2;
  auto t0 = high_resolution_clock::now();
  for (int i = 0; i < 100000000; ++i) {
    hp = hp1;
    hp = std::move(hp2);
  }
  auto t1 = high_resolution_clock::now();
  cout << duration_cast<milliseconds>(t1 - t0).count() << "ms" << endl;
}

class Foo1 {
 public:
  Foo1() {}
  Foo1 sorted() && {
    cout << "call && version" << endl;
    return Foo1();
  }
  Foo1 sorted() const & {
    cout << "call const & version" << endl;
    // Foo1 ret(*this);
    // return ret.sorted();
    return Foo1(*this).sorted();
  }

 private:
  vector<int> data;
};

void t18() {
  // Foo1 f;
  // f.sorted();

  // const Foo1 cf;
  // cf.sorted();

  (Foo1()).sorted();
}

void t19() {
  HasPtrValue hpv("hello");
  cout << hpv.ps << endl;
  HasPtrValue hpv2(std::move(hpv));
  cout << hpv.ps << endl;
  cout << hpv2.ps << endl;

  hpv2 = std::move(hpv2);
  cout << hpv2.ps << endl;
  cout << *hpv2.ps << endl;
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
  t19();
  return 0;
}
