#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

#include "sales_data.h"
#include "sales_item.h"

using std::accumulate;
using std::back_inserter;
using std::begin;
using std::bind;
using std::cin;
using std::count;
using std::count_if;
using std::cout;
using std::distance;
using std::end;
using std::endl;
using std::equal;
using std::fill;
using std::fill_n;
using std::for_each;
using std::front_inserter;
using std::ifstream;
using std::istream_iterator;
using std::list;
using std::ofstream;
using std::ostream;
using std::ostream_iterator;
using std::partition;
using std::runtime_error;
using std::stable_partition;
using std::stable_sort;
using std::sort;
using std::string;
using std::unique;
using std::vector;

using namespace std::placeholders;

void t1() {
  vector<int> vi{1, 2, 3, 4, 5};
  cout << count(vi.begin(), vi.end(), 1) << endl;
}

void t2() {
  ifstream ifs("../src/ch10/words.txt", ifstream::in);

  if (!ifs) {
    throw runtime_error("open failed");
  }

  list<string> ls;
  string word;
  while (ifs >> word) {
    ls.push_back(word);
  }

  cout << count(ls.begin(), ls.end(), "of") << endl;
  cout << count(ls.begin(), ls.end(), "with") << endl;

  string a("awef");
  string b;
  b = a + "awef";

  vector<double> vd{1.0, 2.0, 3.5};
  auto res = accumulate(vd.begin(), vd.end(), 1);
  cout << res << endl;

  vector<int> vd1{1, 2, 300};
  auto res1 = accumulate(vd1.begin(), vd1.end(), 'd');
  cout << res1 << endl;
  cout << 'd' + 300 << endl;

  // 发生了隐式转换
  cout << (string("abd") == "abd") << endl;
  cout << (string("abc") == "abd") << endl;
}

void t3() {
  vector<const char *> vcc{"ab", "bc", "cd"};
  list<const char *> lcc{"ab", "bc", "cd"};

  cout << equal(vcc.begin(), vcc.end(), lcc.begin()) << endl;
  cout << static_cast<void *>(const_cast<char *>(vcc.front())) << endl;
  cout << static_cast<void *>(const_cast<char *>(lcc.front())) << endl;

  const char a[3][3] = {"ab", "bc", "cd"};
  const char b[3][3] = {"ab", "bc", "cd"};
  vector<const char *> vcc1{begin(a), end(a)};
  list<const char *> lcc1{begin(b), end(b)};

  cout << equal(vcc1.begin(), vcc1.end(), lcc1.begin()) << endl;
  cout << static_cast<void *>(const_cast<char *>(vcc1.front())) << endl;
  cout << static_cast<void *>(const_cast<char *>(lcc1.front())) << endl;
}

void t4() {
  vector<int> vi;
  fill_n(back_inserter(vi), 10, 100);

  for (auto i : vi) {
    cout << i << " ";
  }
  cout << endl;

  list<int> li1;
  copy(vi.begin(), vi.end(), back_inserter(li1));

  for (auto i : li1) {
    cout << i << " ";
  }
  cout << endl;

  list<int> li2;
  li2.resize(vi.size());
  copy(vi.begin(), vi.end(), li2.begin());

  // 会先有10个0
  // copy(vi.begin(), vi.end(), back_inserter(li2));

  for (auto i : li2) {
    cout << i << " ";
  }
  cout << endl;

  vector<int> vi1;
  vi1.reserve(vi.size());
  copy(vi.begin(), vi.end(), vi1.begin());

  for (auto i : vi1) {
    cout << i << " ";
  }
  cout << endl;
}

void t5() {
  vector<int> vi{5, 1, 5, 1, 5, 1, 2, 2, 3, 4, 5};
  sort(vi.begin(), vi.end());
  vi.erase(unique(vi.begin(), vi.end()), vi.end());
  for (auto i : vi) {
    cout << i << " ";
  }
  cout << endl;
}

bool CompareIbsn(const Sales_data &lhs, const Sales_data &rhs) {
  return lhs.isbn() < rhs.isbn();
}

void t6() {
  vector<Sales_data> vsd{{"234"}, {"4324"}, {"123"}, {"192"}};
  // sort(vsd.begin(), vsd.end(), CompareIbsn);
  sort(vsd.begin(), vsd.end(),
       [](const Sales_data &lhs, const Sales_data &rhs) {
         return lhs.isbn() < rhs.isbn();
       });

  for (const auto &s : vsd) {
    cout << s.isbn() << " ";
  }
}

bool isLongger5(const string &s) { return s.size() >= 5; }

void t7() {
  vector<string> w{"sdafwefa", "ef", "efa", "feafw", "feafwff"};
  // auto e = partition(w.begin(), w.end(), isLongger5);
  auto e = partition(w.begin(), w.end(),
                     [](const string &s) { return s.size() >= 5; });

  for (auto it = w.cbegin(); it != e; ++it) {
    cout << *it << " ";
  }
}

void t8() {
  auto f = [](int a, int b) { return a + b; };
  // f自动转换为pointer
  int (*pf)(int, int) = f;
  cout << pf(1, 2) << endl;
}

bool checkSize(const string &s, string::size_type sz) { return s.size() >= sz; }

ostream &print(ostream &os, const string &s) { return os << s << " "; }

void biggies(vector<string> &words, vector<string>::size_type sz) {
  sort(words.begin(), words.end());
  words.erase(unique(words.begin(), words.end()), words.end());

  stable_sort(words.begin(), words.end(), [](const string &a, const string &b) {
    return a.size() < b.size();
  });

  // method 1
  // auto wc = find_if(words.begin(), words.end(),
  // [sz](const string &s) { return s.size() >= sz; });
  // cout << words.end() - wc << endl;
  // for_each(wc, words.end(), [](const string &s) { cout << s << " "; });
  // cout << endl;

  // method 2
  // auto wc = find_if(words.begin(), words.end(), bind(checkSize, _1, sz));
  // cout << words.end() - wc << endl;
  // for_each(wc, words.end(), bind(print, ref(cout), _1));
  // cout << endl;

  // method 3
  // auto wc = partition(words.begin(), words.end(),
  // [sz](const string &s) { return s.size() >= sz; });
  // cout << endl;

  // auto wc = stable_partition(words.begin(), words.end(),
  // [sz](const string &s) { return s.size() >= sz; });
  // cout << wc - words.begin() << endl;
  // for_each(words.begin(), wc, [](const string &s) { cout << s << " "; });
  // cout << endl;

  // method 4
  auto wc = partition(words.begin(), words.end(), bind(checkSize, _1, sz));
  cout << wc - words.begin() << endl;
  for_each(words.begin(), wc, bind(print, ref(cout), _1));
  cout << endl;
}

void t9() {
  vector<string> words{"afwe", "ecvjij", "tgoon", "fa", "feq"};
  biggies(words, 4);
}

// auto returnLambda() {
// int a = 10;
// auto res = [a]() -> void { cout << a << endl; };
// return res;
// }

void t10() {
  // returnLambda()();
  int b = 10;
  auto l1 = [b]() {
    int a = 10;
    return [&a, b](int c) {
      cout << a + b + c << endl;
      return a + b + c;
    };
  };

  l1()(10);

  int a = 1;
  int c = 2;

  auto l2 = [a]() mutable {
    ++a;
    return a;
  };
  cout << a << endl;
  cout << l2() << endl;

  auto l3 = [&c]() {
    if (c > 0) {
      ++c;
      return 1;
    } else {
      return 0;
    }
  };
  cout << c << endl;
  cout << l3() << endl;
}

void t11() {
  vector<string> words{"afwe", "ecvjij", "tgoon", "fa", "feq"};
  cout << count_if(words.begin(), words.end(), [](const string &s) {
    return s.size() > 6;
  }) << endl;
}

void t12() {
  int a = 20;
  auto dec = [&a]() {
    while (a > 0) {
      --a;
    }

    return a == 0;
  };

  cout << dec() << endl;
  cout << dec() << endl;
}

void t13() {
  auto l = [](int i) {
    if (i < 0) {
      return -i;
    } else {
      return i;
    }
  };

  cout << l(4) << endl;
}

void t14() {
  istream_iterator<int> int_it(cin);
  istream_iterator<int> eof;

  int tmp;
  istream_iterator<int> old_int_it = int_it++;

  while (int_it != eof) {
    tmp = *old_int_it;
    cout << "inputted: " << tmp << endl;

    int t = *int_it++;
  }
}

void t15() {
  ifstream ifs("../src/ch10/words.tx", ifstream::in);
  istream_iterator<string> it_ifs(ifs);
  istream_iterator<string> eof;
  ostream_iterator<string> it_cout(cout, " ");
  vector<string> vs;

  if (!ifs) {
    cout << "open error" << endl;
    return;
  }

  while (it_ifs != eof) {
    vs.push_back(*it_ifs++);
  }

  copy(vs.begin(), vs.end(), it_cout);
  cout << endl;
}

void t16() {
  istream_iterator<int> it_in(cin);
  istream_iterator<int> eof;
  ostream_iterator<int> it_out(cout, " ");
  vector<int> vi;

  while (it_in != eof) {
    vi.push_back(*it_in++);
  }

  sort(vi.begin(), vi.end());
  // copy(vi.begin(), vi.end(), it_out);
  unique_copy(vi.begin(), vi.end(), it_out);
  cout << endl;
}

void t17() {
  vector<Sales_item> vsi;
  Sales_item item;

  while (cin >> item) {
    vsi.push_back(item);
  }

  copy(vsi.begin(), vsi.end(), ostream_iterator<Sales_item>(cout, " \n"));
}

void t18() {
  vector<Sales_item> vsi;
  istream_iterator<Sales_item> it_in(cin);
  istream_iterator<Sales_item> eof;
  ostream_iterator<Sales_item> it_out(cout, "\n");

  while (it_in != eof) {
    vsi.push_back(*it_in++);
  }

  sort(vsi.begin(), vsi.end(),
       [](const Sales_item &lhs, const Sales_item &rhs) {
         return lhs.isbn() < rhs.isbn();
       });

  for (auto b = vsi.cbegin(), e = b; b != vsi.cend(); b = e) {
    e = find_if(b, vsi.cend(),
                [b](const Sales_item &s) { return s.isbn() != b->isbn(); });
    *it_out = accumulate(b, e, Sales_item());
  }
}

void t19() {
  ifstream ifs("../src/ch10/words.txt", ifstream::in);
  istream_iterator<string> it_in(ifs);
  istream_iterator<string> eof;

  ofstream ofs1("../src/ch10/out1.txt", ofstream::out);
  ofstream ofs2("../src/ch10/out2.txt", ofstream::out);
  ostream_iterator<int> it_out1(ofs1, " ");
  ostream_iterator<int> it_out2(ofs2, " ");

  // while (it_in != eof) {
  // int tmp = (*it_in++)[0];
  // if (tmp % 2 == 0) {
  // *it_out1 = tmp;
  // } else {
  // *it_out2 = tmp;
  // }
  // }

  // 必须是引用
  for_each(it_in, eof, [&it_out1, &it_out2](const string &s) {
    *(static_cast<int>(s[0]) & 0x1 ? it_out1 : it_out2)++ =
        static_cast<int>(s[0]);
  });
}

void t20() {
  vector<int> vi{1, 2, 3, 4, 5};
  for_each(vi.crbegin(), vi.crend(), [](int i) { cout << i << " "; });
  cout << endl;

  for (auto it = vi.cend() - 1; it >= vi.cbegin(); --it) {
    cout << *it << " ";
  }
  cout << endl;

  list<int> li{1, 2, 3, 4, 5, 6, 8, 0, 9, 0, 10};
  list<int>::const_reverse_iterator res_crit =
      find(li.crbegin(), li.crend(), 0);
  list<int>::const_iterator res_cit = find(li.cbegin(), li.cend(), 0);
  list<int>::const_iterator res_it = find(li.begin(), li.end(), 0);

  // 算术运算并不支持list的迭代器!!
  // cout << res_it - li.begin() << endl;

  // vector<int> vi{1, 2, 3, 4, 5, 6, 8, 0, 9, 0, 10};
  // auto res_crit = find(vi.crbegin(), vi.crend(), 0);
  // cout << res_crit - vi.crbegin() << endl;
}

void t21() {
  vector<int> vi{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  list<int> li;
  // 左闭右开区间
  // copy(vi.crbegin() + 3, vi.crbegin() + 8, back_inserter(li));
  copy(vi.cbegin() + 2, vi.cbegin() + 7, front_inserter(li));

  for_each(li.cbegin(), li.cend(), [](int i) { cout << i << " "; });
  cout << endl;
}

void t22() {
  vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  list<int> lst = {1, 2, 3, 4, 0, 5, 6};
  auto found_0 = find(lst.crbegin(), lst.crend(), 0);
  cout << distance(found_0, lst.crend()) << endl;

  // 10.37
  list<int> ret_lst;
  copy(vec.crbegin() + 3, vec.crbegin() + 8, back_inserter(ret_lst));
  //     0, 1, 2, 3, 4, 5, 6, 7, 8, 9
  //    ^                  ^
  // rend                  rbegin
  // @note: copy copies the range [first, last) into result.
  //        hence, the arguments here denote:
  //        [6 5 4 3 2 1)
  //                   ^ this one is specified but not included.
  for (auto i : ret_lst) cout << i << " ";
  cout << endl;
}

void t23() {
  ifstream ifs("../src/ch10/words.txt", ifstream::in);

  if (!ifs) {
    cout << "open error" << endl;
    return;
  }

  istream_iterator<string> it_in(ifs);
  istream_iterator<string> it_eof;
  list<string> ls;

  copy(it_in, it_eof, back_inserter(ls));
  ls.sort();
  ls.unique();

  ostream_iterator<string> it_out(cout, " ");
  copy(ls.begin(), ls.end(), it_out);
  cout << endl;
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
  t23();
  return 0;
}
