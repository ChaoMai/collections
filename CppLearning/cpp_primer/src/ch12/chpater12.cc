#include <cstring>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::allocator;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::initializer_list;
using std::make_pair;
using std::make_shared;
using std::map;
using std::ostream;
using std::out_of_range;
using std::pair;
using std::runtime_error;
using std::set;
using std::shared_ptr;
using std::string;
using std::istringstream;
using std::unique_ptr;
using std::vector;
using std::weak_ptr;

void t1() {
  shared_ptr<string> p = make_shared<string>("hello");
  cout << p.use_count() << endl;
  auto q(p);
  cout << p.use_count() << endl;
  cout << q.use_count() << endl;
}

class StrBlobPtr;
class ConstStrBlobPtr;

class StrBlob {
  friend class StrBlobPtr;
  friend class ConstStrBlobPtr;

 public:
  using size_type = vector<string>::size_type;
  StrBlob();
  StrBlob(initializer_list<string> li);
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  void push_back(const string &t) { data->push_back(t); }
  void pop_back();
  string &front();
  string &front() const;
  string &back();
  string &back() const;
  // as these function need to access the member function of StrBlob, define
  // later
  StrBlobPtr begin();
  StrBlobPtr end();
  ConstStrBlobPtr begin() const;
  ConstStrBlobPtr end() const;

 private:
  shared_ptr<vector<string>> data;
  void check(size_type i, const string &msg) const;
};

StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}

StrBlob::StrBlob(initializer_list<string> li)
    : data(make_shared<vector<string>>(li)) {}

void StrBlob::check(size_type i, const string &msg) const {
  if (i >= data->size()) {
    throw out_of_range(msg);
  }
}

string &StrBlob::front() {
  check(0, "back on empty StrBlob");
  return data->front();
}

string &StrBlob::front() const {
  check(0, "back on empty StrBlob");
  return data->front();
}

string &StrBlob::back() {
  check(0, "back on empty StrBlob");
  return data->back();
}

string &StrBlob::back() const {
  check(0, "back on empty StrBlob");
  return data->back();
}

void StrBlob::pop_back() {
  check(0, "pop_back on empty StrBlob");
  return data->pop_back();
}

bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

class StrBlobPtr {
  friend bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

 public:
  StrBlobPtr() : curr(0) {}
  StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
  string &deref() const;
  StrBlobPtr &incr();

 private:
  shared_ptr<vector<string>> check(size_t, const string &) const;
  weak_ptr<vector<string>> wptr;
  size_t curr;
};

bool equal(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  return lhs.curr == rhs.curr;
}

shared_ptr<vector<string>> StrBlobPtr::check(size_t i,
                                             const string &msg) const {
  auto ret = wptr.lock();

  if (!ret) {
    throw runtime_error("unbound StrBlobPtr");
  }

  if (i >= ret->size()) {
    throw out_of_range(msg);
  }

  return ret;
}

string &StrBlobPtr::deref() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

StrBlobPtr &StrBlobPtr::incr() {
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end() {
  auto ret = StrBlobPtr(*this, data->size());
  return ret;
}

bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

class ConstStrBlobPtr {
  friend bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);

 public:
  ConstStrBlobPtr() : curr(0) {}
  ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
  const string &deref() const;
  ConstStrBlobPtr &incr();

 private:
  shared_ptr<vector<string>> check(size_t, const string &) const;
  weak_ptr<vector<string>> wptr;
  size_t curr;
};

bool equal(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs) {
  return lhs.curr == rhs.curr;
}

shared_ptr<vector<string>> ConstStrBlobPtr::check(size_t i,
                                                  const string &msg) const {
  auto ret = wptr.lock();

  if (!ret) {
    throw runtime_error("unbound StrBlobPtr");
  }

  if (i >= ret->size()) {
    throw out_of_range(msg);
  }

  return ret;
}

const string &ConstStrBlobPtr::deref() const {
  auto p = check(curr, "dereference past end");
  return (*p)[curr];
}

ConstStrBlobPtr &ConstStrBlobPtr::incr() {
  check(curr, "increment past end of StrBlobPtr");
  ++curr;
  return *this;
}

ConstStrBlobPtr StrBlob::begin() const { return ConstStrBlobPtr(*this); }

ConstStrBlobPtr StrBlob::end() const {
  auto ret = ConstStrBlobPtr(*this, data->size());
  return ret;
}

void t2() {
  int i = 5;
  int *pi = &i;
  // segmentation fault with clang++
  // delete pi;

  int *pi2 = nullptr;
  delete pi2;

  double *pd = new double(3);
  delete pd;
  cout << pd << endl;
  // delete pd;

  const int *pci = new const int(1024);
  delete pci;
}

void AddNum(vector<int> *pv) {
  for (int i = 0; i < 1000000000; ++i) {
    pv->push_back(i);
  }
}

void t3() {
  vector<int> *pv = new vector<int>();
  AddNum(pv);
  // delete pv;
}

void t4() {
  StrBlob sb({"1123"});
  StrBlob sb1 = {"123"};
}

class ExplicitTest {
 public:
  ExplicitTest(int i) { ++count; }

  static int count;
};

int ExplicitTest::count = 1;

void t5() {
  ExplicitTest et = 1;
  cout << et.count << endl;
}

void t6() {
  vector<int> vi;
  // 错误
  // constexpr int s = vi.size();
  const int s = vi.size();
}

void t7() {
  shared_ptr<int> p(make_shared<int>(4));
  int *q = p.get();
  {
    shared_ptr<int> sq(q);
    cout << "1: " << *sq << endl;
    // delete q;
    cout << "2: " << *sq << endl;
  }
  // cout << "3: " << *p << endl;
}

class C {
 public:
  C() {
    cout << __func__ << " Default Consturctor" << endl;
    cout << "before:" << endl;
    PrintStatus();
    ++ConsCount;
    cout << "after:" << endl;
    PrintStatus();
    cout << endl;
  }
  C(const C &) {
    cout << __func__ << " Copy Constructor" << endl;
    cout << "before:" << endl;
    PrintStatus();
    ++CopyCount;
    cout << "after:" << endl;
    PrintStatus();
    cout << endl;
  }
  ~C() {
    cout << __func__ << endl;
    cout << "before:" << endl;
    PrintStatus();
    ++DesCount;
    cout << "after:" << endl;
    PrintStatus();
    cout << endl;
  }

  static int ConsCount;
  static int CopyCount;
  static int DesCount;

 private:
  void PrintStatus() {
    cout << "ConsCount: " << ConsCount << endl
         << "CopyCount: " << CopyCount << endl
         << "DesCount: " << DesCount << endl;
  }
};

int C::ConsCount = 0;
int C::CopyCount = 0;
int C::DesCount = 0;

void p(C c) {}

void t8() {
  C c;
  // p(c);
  // p(C(c));
  C cc(c);
  // p(cc);
}

void process(shared_ptr<int> p) {
  cout << __func__ << ": " << p.use_count() << endl;
}

void t9() {
  shared_ptr<int> p(new int(42));
  cout << __func__ << ": " << p.use_count() << endl;
  process(shared_ptr<int>(p));
  // process(p);
}

void t10() {
  shared_ptr<int> p(make_shared<int>(10));
  shared_ptr<int> q;
  // 错误
  // q.reset(p);
}

void t11() {
  unique_ptr<int> p(new int(10));
  // 错误
  // unique_ptr<int> q(p);
  unique_ptr<int> q;
  // 错误
  // q = p;
}

void t12() {
  const StrBlob sb{"vcsav", "awef", "fnnu"};
  for (ConstStrBlobPtr b = sb.begin(); !equal(b, sb.end()); b.incr()) {
    cout << b.deref() << endl;
  }
}

void t13() {
  int a[32] = {0};
  for (auto &e : a) {
    e += 1;
  }

  for (const auto e : a) {
    cout << e << endl;
  }

  shared_ptr<int> p;
  cout << (p == nullptr) << endl;
}

void t14() {
  const char *str1 = "hello, ";
  const char *str2 = "world";

  // strlen, not sizeof
  unique_ptr<char[]> str3(new char[strlen(str1) + strlen(str2)]);

  // for (size_t i = 0; i < strlen(str1); ++i) {
  // str3[i] = str1[i];
  // }

  // for (size_t i = 0; i < strlen(str2); ++i) {
  // str3[strlen(str1) + i] = str2[i];
  // }

  // for (size_t i = 0; i < strlen(str1) + strlen(str2); ++i) {
  // cout << str3[i] << "|";
  // }
  // cout << endl;

  // cout << strlen(str3.get()) << " " << str3.get() << endl;

  strcat(str3.get(), str1);
  strcat(str3.get(), str2);
  cout << strlen(str3.get()) << " " << str3.get() << endl;
}

void t15() {
  unique_ptr<char[]> str(new char[256]);
  cin.getline(str.get(), 256);
  cout << str.get() << endl;
}

void t16() {
  class C {
   public:
    // C() = default;
    C(int a, int b) : a_(a), b_(b) {}

    int a_;
    int b_;
  };

  // 错误
  // C *const pc = new C[5]{1, 2};

  allocator<C>::size_type n = 10;
  allocator<C> alloc;
  auto const p = alloc.allocate(n);
  // C *const p1 = alloc.allocate(10);
  auto q = p;
  alloc.construct(q++, 1, 2);  // 类似make_shared
  cout << p->a_ << " " << p->b_ << endl;
  cout << q->a_ << " " << q->b_ << endl;  // 错误，q指向的内存未构造

  while (q != p) {
    alloc.destroy(--q);
  }

  alloc.deallocate(p, n);
}

void t17() {
  int i = 5;
  const auto cap = &i;   // int *const cap
  auto const cap1 = &i;  // int *const cap1
  *cap = 1;
  // ++cap;
  *cap1 = 1;
  // ++cap1;
  cout << i << endl;

  const auto &car = i;   // const int &car
  auto const &car1 = i;  // const int &car1
  // car = 1;
  // car1 = 1;
}

// class QueryResult {
// friend void print(ostream &os, const QueryResult &pqr);

// public:
// using line_no = vector<string>::size_type;
// QueryResult(string s, shared_ptr<set<line_no>> p,
// shared_ptr<vector<string>> f)
// : sought(s), lines(p), file(f) {}

// private:
// string sought;
// shared_ptr<set<line_no>> lines;
// shared_ptr<vector<string>> file;
// };

// void print(ostream &os, const QueryResult &qr) {}

// class TextQuery {
// public:
// using line_no = vector<string>::size_type;
// TextQuery(ifstream &ifs);
// QueryResult query(const string &s);

// private:
// shared_ptr<vector<string>> file;
// map<string, shared_ptr<set<line_no>>> wm;
// };

// TextQuery::TextQuery(ifstream &ifs) : file(new vector<string>) {
// string text;
// while (getline(ifs, text)) {
// file->push_back(text);
// line_no n = file->size() - 1;
// istringstream line(text);
// string word;
// while (line >> word) {
// auto &lines = wm[word];
// if (lines == nullptr) {
// lines.reset(new set<line_no>);
// }
// lines->insert(n);
// }
// }
// }

// QueryResult TextQuery::query(const string &s) {
// static shared_ptr<set<line_no>> nodata(new set<line_no>);
// auto loc = wm.find(s);
// if (locc == wm.end()) {
// return QueryResult(s, nodata, file);
// } else {
// return QueryResult(s, loc->second, file);
// }
// }

class QueryResult {
  friend void print(ostream &os, const QueryResult &pqr);

 public:
  using line_no = vector<string>::size_type;
  QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<StrBlob> f)
      : sought(s), lines(p), file(f) {}
  set<line_no>::iterator begin() { return lines->begin(); }
  set<line_no>::iterator end() { return lines->end(); }
  shared_ptr<StrBlob> get_file() { return file; }

 private:
  string sought;
  shared_ptr<set<line_no>> lines;
  shared_ptr<StrBlob> file;
};

void print(ostream &os, const QueryResult &qr) {}

class TextQuery {
 public:
  using line_no = vector<string>::size_type;
  TextQuery(ifstream &ifs);
  QueryResult query(const string &s);

 private:
  shared_ptr<StrBlob> file;
  map<string, shared_ptr<set<line_no>>> wm;
};

TextQuery::TextQuery(ifstream &ifs) : file(new StrBlob) {
  string text;
  while (getline(ifs, text)) {
    file->push_back(text);
    line_no n = file->size() - 1;
    istringstream line(text);
    string word;
    while (line >> word) {
      auto &lines = wm[word];
      if (lines == nullptr) {
        lines.reset(new set<line_no>);
      }
      lines->insert(n);
    }
  }
}

QueryResult TextQuery::query(const string &s) {
  static shared_ptr<set<line_no>> nodata(new set<line_no>);
  auto loc = wm.find(s);
  if (loc == wm.end()) {
    return QueryResult(s, nodata, file);
  } else {
    return QueryResult(s, loc->second, file);
  }
}

void t18() {
  ifstream ifs("../src/ch12/story.txt", ifstream::in);
  if (!ifs) {
    cerr << "open file error" << endl;
  }

  TextQuery tq(ifs);
  while (true) {
    cout << "enter word to look for, or q to quit: ";
    string s;
    if (!(cin >> s) || s == "q") {
      break;
    }
    print(cout, tq.query(s));
  }
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
  return 0;
}
