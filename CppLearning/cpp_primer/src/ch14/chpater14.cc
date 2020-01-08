#include <algorithm>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "conststrblobptr.h"
#include "inputstring.h"
#include "sales_data.h"
#include "str.h"
#include "strblob.h"
#include "strblobptr.h"
#include "strvec.h"

using std::all_of;
using std::bind;
using std::cin;
using std::cout;
using std::count_if;
using std::divides;
using std::endl;
using std::find_if;
using std::function;
using std::greater;
using std::initializer_list;
using std::make_shared;
using std::map;
using std::minus;
using std::modulus;
using std::multiplies;
using std::not_equal_to;
using std::plus;
using std::replace_if;
using std::string;
using std::transform;
using std::vector;
using std::weak_ptr;

void t1() {
  Str str("hello, world");
  cout << str << endl;
}

void t2() {
  double d;
  cin >> d;
  cout << d << endl;
}

void t3() {
  Sales_data item;
  cin >> item;
  cout << item << endl;
}

void t4() {
  Sales_data i1;
  Sales_data i2;

  cout << (i1 + i2) << endl;
}

void t5() {
  Str str1("asdf");
  Str str2("asdf");
  cout << (str1 == str2) << endl;
  Str str3("asdfg");
  cout << (str1 == str3) << endl;
  cout << str1[1] << endl;
}

void t6() {
  StrVec sv1{"1", "12", "123"};
  StrVec sv2{"1", "12", "123"};
  cout << (sv1 == sv2) << endl;
  StrVec sv3{"1", "12", "1234"};
  cout << (sv1 == sv3) << endl;
  cout << sv1[2] << endl;
}

void t7() {
  StrBlob sb{"1", "12", "123"};
  cout << sb[1] << endl;
}

void t8() {
  StrBlob sb{"1", "12", "123"};
  StrBlobPtr p(sb);
  cout << *p << endl;
  ++p;
  cout << *p << endl;
  p += 1;
  cout << *p << endl;
  cout << p->size() << endl;
  *p = "awef";
  cout << *p << endl;
  p = p + 1;
  cout << *p << endl;
}

void t9() {
  const StrBlob sb{"1", "12", "123"};
  ConstStrBlobPtr p(sb);
  cout << *p << endl;
}

void t10() {
  class Choose {
   public:
    int operator()(int a, int b, int c) const { return a ? b : c; }
  };

  Choose ch;
  cout << ch(1, 2, 3) << endl;
}

void t11() {
  InputString is;
  vector<string> vs;
  string line;
  while (!(line = is()).empty()) {
    vs.push_back(line);
  }

  for (auto &s : vs) {
    cout << s << endl;
  }
}

void t12() {
  class Equal {
   public:
    Equal(int b) : b_(b) {}
    bool operator()(int a) const { return a == b_; }

   private:
    int b_;
  };

  vector<int> vi{1, 2, 1, 4, 1, 6};
  // replace_if(vi.begin(), vi.end(), bind(eq, std::placeholders::_1, 1), 10);
  replace_if(vi.begin(), vi.end(), Equal(1), 10);

  for (auto &s : vi) {
    cout << s << endl;
  }
}

void t13() {
  class EqualLength {
   public:
    EqualLength(string::size_type i) : i_(i) {}
    bool operator()(const string &s) { return s.size() == i_; }

   private:
    string::size_type i_;
  };

  map<int, int> count;

  string word;
  while (cin >> word) {
    ++count[word.size()];
  }

  for (auto &p : count) {
    cout << p.first << " " << p.second << endl;
  }
}

void t14() {
  vector<int> vi{213, 234234, 12341, 123, 1, 1, 1};
  cout << count_if(vi.begin(), vi.end(),
                   bind(greater<int>(), std::placeholders::_1, 1024))
       << endl;

  cout << *find_if(vi.begin(), vi.end(),
                   bind(not_equal_to<int>(), std::placeholders::_1, 213))
       << endl;

  transform(vi.begin(), vi.end(), vi.begin(),
            bind(multiplies<int>(), std::placeholders::_1, 2));
  for (auto i : vi) {
    cout << i << endl;
  }

  cout << count_if(vi.begin(), vi.end(),
                   bind(modulus<int>(), std::placeholders::_1, 2))
       << endl;

  cout << all_of(vi.begin(), vi.end(), [](int i) {
    return 0 == modulus<int>()(i, 2);
  }) << endl;
}

void t15() {
  map<string, function<int(int, int)>> binops = {{"+", plus<int>()},
                                                 {"-", minus<int>()},
                                                 {"*", multiplies<int>()},
                                                 {"/", divides<int>()},
                                                 {"%", modulus<int>()}};

  cout << binops["*"](10, 2) << endl;
}

void t16() {
  class S {
   public:
    S(int i = 0) : val(i) { cout << "construct" << endl; }
    S(const S &s) : val(s.val) { cout << "copy" << endl; }
    S(S &&s) : val(s.val) { cout << "move" << endl; }
    S &operator=(const S &s) {
      cout << "copy assign" << endl;
      val = s.val;
      return *this;
    }
    S &operator=(S &&s) {
      cout << "move assign" << endl;
      val = s.val;
      return *this;
    }
    operator int() const {
      cout << "conversion->int" << endl;
      return val;
    }

   private:
    size_t val;
  };

  S s;
  s = 4;
  s + 3;
  s = 3.14;
  s + 3.14;
  s - s;
}

void t17() {
  class S {
   public:
    S(int i = 0) : val(i) { cout << "construct" << endl; }
    explicit operator bool() const {
      cout << "conversion->bool" << endl;
      return val;
    }
    operator int() const {
      cout << "conversion->int" << endl;
      return val;
    }
    // int operator+(int rhs) {
    // cout << "call +" << endl;
    // return val + rhs;
    // }

   private:
    size_t val;
  };

  S s(10);
  if (s) {
  }

  s + 1;
}

class SmallInt {
  friend SmallInt operator+(const SmallInt &, const SmallInt &);

 public:
  SmallInt() = default;
  operator int() const { return 0; }
  operator double() const { return 0; }
};

SmallInt operator+(const SmallInt &, const SmallInt &) {}

class LongDouble {
 public:
  LongDouble() = default;
  LongDouble operator+(const SmallInt &) {}
  operator double() const { return 0; }
  operator float() const { return 0; }
};

LongDouble operator+(LongDouble &, double) {}

void t18() {
  SmallInt si;
  LongDouble ld;

  // ld = si + ld;
  ld = ld + si;
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
  t18();
  // t19();
  return 0;
}
