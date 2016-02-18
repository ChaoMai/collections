#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

void t1() { list<deque<int>> ldeq; }

// 不能是这样的const，因为无法进行++操作
// bool find(const vector<int>::const_iterator begin, ...
bool find1(vector<int>::const_iterator begin, vector<int>::const_iterator end,
           int val) {
  while (begin != end) {
    if (*begin == val) {
      return true;
    }
    ++begin;
  }
  return false;
}

// simpler, but only c++14
// auto find2(vector<int>::const_iterator begin, vector<int>::const_iterator
// end, int val) {
vector<int>::const_iterator find2(vector<int>::const_iterator begin,
                                  vector<int>::const_iterator end, int val) {
  while (begin != end) {
    if (*begin == val) {
      return begin;
    }
    ++begin;
  }
  return end;
}

void t2() {
  vector<int> va{1, 2, 3, 4, 5, 6, 7};
  cout << boolalpha << find1(va.cbegin(), va.cend(), 6) << endl
       << (find2(va.begin(), va.end(), 5) == va.end() ? false : true) << endl
       << (find2(va.begin(), va.end(), 50) == va.end() ? false : true) << endl;
}

void t3() {
  vector<int>::size_type index;
  vector<int>::value_type ia;

  const list<int> ss{1, 2, 3, 4, 5};
  list<int>::const_iterator it = ss.begin();

  vector<int> v1;
  const vector<int> v2;
  // 以下代码错误，it1与it2类型不同，无法位于同一条语句
  // auto it1 = v2.begin(), it2 = v1.begin();
  // auto it3 = v1.cbegin(), it4 = v2.cbegin();
  auto it1 = v1.begin();
  auto it2 = v2.begin(), it3 = v1.cbegin(), it4 = v2.cbegin();

  int a1 = 0;
  const int a2 = 0;
  // 问题类似上面的
  // 此时底层const保留
  // auto *pa1 = &a1, *pa2 = &a2;
  // const auto *pa1 = &a1, *pa2 = &a2;
  const auto *const pa1 = &a1, *pa2 = &a2;
}

void t4() {
  class A {
   public:
    // A() = default;
    A(int a, int b) : a_(a), b_(b) {}
    // explicit A(int a, int b) : a_(a), b_(b) {}
    int a_ = 0;
    int b_ = 0;
  };

  // 必须提供A的默认构造函数
  // vector<A> as(10);

  vector<A> as(10, {1, 2});
  // 如果是explicit构造函数，则必须显示构造出A
  // vector<A> as(10, A(1, 2));

  A a{1, 3};
}

void t5() {
  class E {
   public:
    E() = default;
    E(int i) : a(i) {}

   private:
    int a = 0;
  };

  vector<E> oe{1, 2, 3};

  vector<E> e1(oe);
  vector<E> e2 = oe;
  vector<E> e3{1, 2, 3};
  vector<E> e4 = {E(1), E(2), E(3)};
  vector<E> e5(oe.begin(), oe.begin() + 1);
  vector<E> e6(10);
  vector<E> e7(10, 1);
  vector<E> e8(10, E(1));
}

void t6() {
  list<int> li{1, 2, 3, 4, 5, 6};
  vector<double> vd1(li.begin(), li.end());

  vector<int> vi{1, 2, 3, 4, 5, 6};
  vector<double> vd2(vi.begin(), vi.end());

  // won't work
  // vector<double> vd3(vi);
}

void t7() {
  // 不可直接使用char*
  list<const char *> lc{"hello", "world"};
  vector<string> vs(lc.cbegin(), lc.cend());
  cout << vs.size() << endl;
  cout << vs[0] << " " << vs[1] << endl;

  vector<string> vs1;
  vs1.assign(lc.cbegin(), lc.cend());
  cout << vs1.size() << endl;
  cout << vs1[0] << " " << vs1[1] << endl;

  class A {
   public:
    A(int a) : a_(a) {}

   private:
    int a_;
  };

  vector<A> as;
  // 10个元素每个都是A的对象
  as.assign(10, 1);

  // 不可直接使用char*
  char *chs = "abcdef";
  cout << chs << endl;
  // core dump
  // chs[0] = 'z';
}

void t8() {
  vector<int> a{1, 2, 3};
  vector<int> b{1, 2, 3, 4};
  cout << boolalpha << (a == b) << endl;

  list<int> l{1, 2, 3, 4};
  cout << (vector<int>(l.begin(), l.end()) == b) << endl;
  vector<int> vl;
  vl.assign(l.begin(), l.end());
  cout << (vl == b) << endl;
}

void t9() {
  class C1 {
   public:
    C1(int a) : a_(a) {}

   private:
    int a_;
  };

  vector<C1> cs;
  cs.push_back(1);

  class C2 {
   public:
    C2() = default;
    explicit C2(int a) : a_(a) {}
    C2(int a, int b) : a_(a), b_(b) {}

   private:
    int a_ = 0;
    int b_ = 0;
  };

  vector<C2> cs2;
  // 由于是explicit，不存在从int到C2的隐式转换
  // cs2.push_back();
  // cs2.push_back(1);
  // cs2.push_back(1, 2);
  cs2.push_back(C2());
  cs2.push_back(C2(1));
  cs2.push_back(C2(1, 2));

  // 调用了C2的构造函数
  cs2.emplace_back();
  cs2.emplace_back(1);
  cs2.emplace_back(1, 2);
}

void t10() {
  deque<string> ds;

  string word;
  while (cin >> word) {
    ds.push_back(word);
  }

  for (auto &s : ds) {
    cout << s << endl;
  }
}

void t11() {
  list<string> ds;

  for (string word; cin >> word; ds.push_back(word))
    ;

  for (auto &s : ds) {
    cout << s << endl;
  }
}

void t12() {
  list<int> li{1, 2, 3, 4, 5, 6, 7, 8, 9};
  deque<int> d1;
  deque<int> d2;

  for (auto i : li) {
    if (i % 2 == 0) {
      d1.push_back(i);
    } else {
      d2.push_back(i);
    }
  }

  for (auto &s : d1) {
    cout << s;
  }

  cout << endl;
  for (auto &s : d2) {
    cout << s;
  }
}

void t13() {
  list<int> li{1, 2, 3, 4, 5, 6, 7, 8, 9};
  deque<int> d1;
  deque<int> d2;

  for (auto i : li) {
    (i & 0x1 ? d1 : d2).push_back(i);
  }

  for (auto &s : d1) {
    cout << s;
  }

  cout << endl;
  for (auto &s : d2) {
    cout << s;
  }
}

void t14() {
  vector<int> iv{1, 2, 1, 2, 3, 1, 3, 4, 1};

  vector<int>::iterator iter = iv.begin();
  vector<int>::size_type half_size = iv.size() / 2;

  while (iter !=
         (iv.end() - static_cast<vector<int>::difference_type>(half_size))) {
    if (*iter == 1) {
      iter = iv.insert(iter, 2 * 1);
      iter += 2;
    } else {
      ++iter;
    }
  }

  for (auto s : iv) {
    cout << s << " ";
  }
}

void t15() {
  vector<int> v{1, 2, 3, 4, 5};
  v.erase(v.end(), v.end());

  for (auto i : v) {
    cout << i << endl;
  }

  int ia[] = {0, 1, 2, 3, 4, 5, 6, 7};
  // vector<int>via(begin(ia), end(ia));
  vector<int> via(ia, end(ia));
  list<int> lia(via.begin(), via.end());

  auto vit = via.begin();
  while (vit != via.end()) {
    if (*vit % 2 == 0) {
      vit = via.erase(vit);
    } else {
      ++vit;
    }
  }

  auto lit = lia.begin();
  while (lit != lia.end()) {
    if (*lit % 2 != 0) {
      lit = lia.erase(lit);
    } else {
      ++lit;
    }
  }

  for (auto i : via) {
    cout << i << " ";
  }

  cout << endl;
  for (auto i : lia) {
    cout << i << " ";
  }
}

void t16() {
  forward_list<int> fl{0, 1, 2, 3, 4, 5, 6, 7};
  auto pre = fl.before_begin();
  auto cur = fl.begin();

  while (cur != fl.end()) {
    if (*cur % 2 != 0) {
      cur = fl.erase_after(pre);
    } else {
      pre = cur;
      ++cur;
    }
  }

  for (auto i : fl) {
    cout << i << " ";
  }
}

void insertString(forward_list<string> &fls, const string &s1,
                  const string &s2) {
  auto pre = fls.before_begin();
  auto cur = fls.begin();

  while (cur != fls.end()) {
    if (*cur == s1) {
      fls.insert_after(cur, s2);
      break;
    } else {
      pre = cur;
      ++cur;
    }
  }

  if (cur == fls.end()) {
    fls.insert_after(pre, s2);
  }
}

void insertString2(forward_list<string> &fls, const string &s1,
                   const string &s2) {
  auto pre = fls.before_begin();

  for (auto cur = fls.begin(); cur != fls.end(); pre = cur++) {
    if (*cur == s1) {
      fls.insert_after(cur, s2);
      return;
    }
  }

  fls.insert_after(pre, s2);
}

void t17() {
  forward_list<string> fls{"afef", "feawf", "fawef"};
  // insertString(fls, "feawf", "aaaa");
  // insertString(fls, "awf", "aaaa");
  insertString2(fls, "awf", "aaaa");

  for (const auto s : fls) {
    cout << s << " ";
  }
}

void t18() {
  vector<int> vi{1, 2, 3, 4, 5};

  auto old_end = vi.end();
  auto old_last_2 = old_end - 2;

  vi.pop_back();
  vi.pop_back();
  cout << boolalpha << (old_last_2 == vi.end());
  cout << *(vi.end()++) << " ";
}

void t19() {
  forward_list<int> fli = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (auto cur = fli.begin(), pre = fli.before_begin(); cur != fli.end();) {
    if (*cur % 2 != 0) {
      pre = fli.insert_after(pre, *cur);
      ++pre;
      ++cur;
    } else {
      cur = fli.erase_after(pre);
    }
  }

  for (auto i : fli) {
    cout << i << " ";
  }
}

void t20() {
  list<int> li = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  for (auto cur = li.begin(); cur != li.end();) {
    if (*cur % 2 != 0) {
      // 不合法，求值顺序未定义
      // li.insert(cur, *cur++);
      li.insert(cur, *cur);
      ++cur;
    } else {
      cur = li.erase(cur);
    }
  }

  for (auto i : li) {
    cout << i << " ";
  }
}

void t21() {
  vector<int> vi{0, 1, 2, 3, 4};
  // auto iter = vi.begin();

  // while (iter != vi.end()) {
  // if (*iter % 2 != 0) {
  // iter = vi.insert(iter, *iter);
  // }
  // ++iter;
  // }

  for (auto iter = vi.begin(); iter != vi.end(); ++iter) {
    if (*iter % 2 != 0) {
      iter = vi.insert(iter, *iter);
      ++iter;
    }
  }

  for (auto i : vi) {
    cout << i << " ";
  }
}

void t22() {
  vector<int> v;
  // v.reserve(1024);

  for (int i = 1; i <= 1025; ++i) {
    v.push_back(i);
    if (i % 10 == 0) {
      cout << "size: " << v.size() << " capacity: " << v.capacity() << endl;
    }
  }

  cout << "size: " << v.size() << " capacity: " << v.capacity() << endl;
}

void printCapacity(const vector<int> &v) {
  cout << "size: " << v.size() << " capacity: " << v.capacity() << endl;
}

void t23() {
  vector<int> v1(10, 10);
  vector<int> v2(10, 10);
  printCapacity(v1);
  printCapacity(v2);

  v1.resize(15);
  v2.reserve(15);

  printCapacity(v1);
  printCapacity(v2);
}

void t24() {
  const char *cp = "hello, world";
  string s1(cp);
  cout << s1 << endl;

  char chs[] = {'h', 'e', 'l', 'l', 'o'};
  string s2(chs, sizeof(chs));
  cout << sizeof(chs) << " " << s2 << endl;

  vector<char> vc{'h', 'e', 'l', 'l', 'o'};
  string s3(vc.begin(), vc.end());
  cout << s3 << endl;

  string s4;
  s4.reserve(200);
  cout << s4.capacity() << endl;
}

void Substitute1(string &s, const string &oldVal, const string &newVal) {
  for (int i = 0; i != s.size();) {
    // 下标不同于迭代器，
    // 无论i位于什么位置，最多只会拷贝到s的末尾
    string tmp(s, i, oldVal.size());
    if (tmp == oldVal) {
      s.erase(i, oldVal.size());
      s.insert(i, newVal);
      i += newVal.size();
    } else {
      ++i;
    }
  }
}

void Substitute2(string &s, const string &oldVal, const string &newVal) {
  for (auto it = s.begin(); it + oldVal.size() <= s.end();) {
    // 不是下标，需要检查it后面是否有足够的长的字符来拷贝
    string tmp(it, it + oldVal.size());
    if (tmp == oldVal) {
      // 两个操作都会使得it失效
      it = s.erase(it, it + oldVal.size());
      it = s.insert(it, newVal.begin(), newVal.end());
      it += newVal.size();
    } else {
      ++it;
    }
  }
}

void Substitute3(string &s, const string &oldVal, const string &newVal) {
  s.replace(0, oldVal.size(), newVal);
  s.replace(newVal.size() + 1, oldVal.size(), newVal);
}

void Substitute4(string &s, const string &oldVal, const string &newVal) {
  s.replace(s.begin(), s.begin() + oldVal.size(), newVal);
  s.replace(s.begin() + newVal.size() + 1, s.end(), newVal);
}

void t25() {
  // string s1("tho tho tho thofaf afwefthoafwthoth");
  string s1("tho tho tho thofaf afwefthoafwthotho");
  string s2(s1);
  string s3(s1);
  string s4(s1);
  Substitute1(s1, "tho", "though");
  cout << s1 << endl;

  Substitute2(s2, "tho", "though");
  cout << s2 << endl;

  Substitute3(s3, "tho", "though");
  cout << s3 << endl;

  Substitute4(s4, "tho", "though");
  cout << s4 << endl;
}

string WrapString1(const string &s, const string &prefix,
                   const string &suffix) {
  // return prefix + s + " " + suffix;
  string tmp(s);
  tmp.insert(tmp.begin(), prefix.begin(), prefix.end());
  tmp.insert(tmp.begin() + prefix.size(), 1, ' ');
  tmp.append(" " + suffix);

  return tmp;
}

string WrapString2(const string &s, const string &prefix,
                   const string &suffix) {
  string tmp(s);
  tmp.insert(0, prefix);
  tmp.insert(prefix.size(), " ");
  tmp.insert(tmp.size(), " ");
  tmp.insert(tmp.size(), suffix);

  return tmp;
}

void t26() {
  cout << WrapString1("Chao Mai", "Mr.", "Jr.") << endl;
  cout << WrapString2("Chao Mai", "Mr.", "Jr.") << endl;
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
  t25();
  // t26();
  return 0;
}
