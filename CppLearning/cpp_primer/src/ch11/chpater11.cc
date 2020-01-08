#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using std::cin;
using std::cout;
using std::boolalpha;
using std::endl;
using std::find;
using std::for_each;
using std::ifstream;
using std::istream_iterator;
using std::list;
using std::map;
using std::multiset;
using std::multimap;
using std::pair;
using std::runtime_error;
using std::set;
using std::string;
using std::istringstream;
using std::unordered_map;
using std::vector;

string trim(const string s, char to_trim) {
  return s.substr(s.find_first_not_of(to_trim))
      .substr(0, s.find_last_of(to_trim));
}

void t1() {
  ifstream ifs("../src/ch10/words.txt", ifstream::in);

  if (!ifs) {
    cout << "open error" << endl;
  }

  istream_iterator<string> it_in(ifs);
  istream_iterator<string> it_eof;
  map<string, size_t> count;

  for_each(it_in, it_eof, [&count](const string& s) {
    ++count[trim(trim(trim(s, ','), '.'), '"')];
  });
  for_each(count.begin(), count.end(), [](const pair<string, size_t>& s) {
    cout << s.first << " " << s.second << endl;
  });
}

void t2() {
  map<string, vector<string>> names;
  string last_name;
  cin >> last_name;
  string first_name;

  while (cin >> first_name) {
    names[last_name].push_back(first_name);
  }

  for_each(names.begin(), names.end(),
           [](const pair<string, vector<string>>& names) {
             for_each(names.second.begin(), names.second.end(),
                      [&names](const string& s) {
                        cout << names.first << " " << s << endl;
                      });
           });
}

void t3() {
  ifstream ifs("../src/ch10/words.txt", ifstream::in);

  if (!ifs) {
    cout << "open error" << endl;
  }

  istream_iterator<string> it_in(ifs);
  istream_iterator<string> eof;

  vector<string> vs;
  for_each(it_in, eof, [&it_in, &vs](const string& s) {
    string word = trim(trim(trim(*it_in++, ','), '.'), '"');

    if (find(vs.cbegin(), vs.cend(), word) == vs.cend()) {
      vs.push_back(word);
    }
  });
  for_each(vs.begin(), vs.end(), [](const string& s) { cout << s << " "; });
}

void t4() {
  auto comp = [](int a, int b) { return false; };
  multiset<int, bool (*)(const int, const int)> m(comp);

  auto comp1 = [](const int a, const int b) { return false; };
  multiset<int, bool (*)(int, int)> m1(comp1);

  auto comp2 = [](int* const a, int* const b) { return false; };
  multiset<int, bool (*)(int*, int*)> m2(comp2);

  auto comp3 = [](int* a, int* b) { return false; };
  multiset<int, bool (*)(int* const, int* const)> m3(comp3);

  // auto comp4 = [](int* a, int* b) { return false; };
  // multiset<int, bool (*)(const int*, const int*)> m4(comp4);
}

void t5() {
  ifstream ifs("../src/ch10/words.txt", ifstream::in);

  if (!ifs) {
    cout << "open error" << endl;
  }

  map<string, list<int>> ml;

  int row_num = 0;
  string line;
  while (getline(ifs, line)) {
    ++row_num;
    istringstream iss(line);
    string word;
    while (iss >> word) {
      ml[word].push_back(row_num);
    }
  }

  for_each(ml.begin(), ml.end(), [](const pair<string, list<int>>& p) {
    cout << p.first << ": ";
    for_each(p.second.begin(), p.second.end(),
             [](const int r) { cout << r << " "; });
    cout << endl;
  });
}

void t6() {
  map<vector<int>::iterator, int> mv;
  map<list<int>::iterator, int> ml;

  // 错误
  // list<int> li;
  // ml[li.begin()] = 0;
}

vector<int> fun() { return {1, 2, 3, 4, 5}; }

void t7() {
  // 错误，两次fun调用，1. 顺序未知；2. 返回了两个对象
  for_each(fun().begin(), fun().end(), [](const int i) { cout << i << " "; });
  cout << endl;
}

void t8() {
  ifstream ifs("../src/ch10/words.txt", ifstream::in);

  if (!ifs) {
    cout << "open error" << endl;
  }

  istream_iterator<string> it_in(ifs);
  istream_iterator<string> it_eof;
  vector<pair<string, int>> vp;
  int count = 0;
  for_each(it_in, it_eof, [&count, &vp](const string& s) {
    // vp.push_back(make_pair(s, count++));
    // vp.push_back(pair<string, int>(s, count++));
    // vp.push_back({s, count++});
    vp.emplace_back(s, count++);
  });

  for_each(vp.begin(), vp.end(), [](const pair<string, int>& p) {
    cout << p.first << " " << p.second << " ";
  });
  cout << endl;
}

void t9() {
  ifstream ifs("../src/ch10/words.txt", ifstream::in);

  if (!ifs) {
    cout << "open error" << endl;
  }

  istream_iterator<string> it_in(ifs);
  istream_iterator<string> it_eof;
  map<string, size_t> count;

  for_each(it_in, it_eof, [&count](const string& s) {
    // ++count[s];
    pair<map<string, size_t>::iterator, bool> p = count.insert({s, 1});
    if (!p.second) {
      ++p.first->second;
    }
  });
  for_each(count.begin(), count.end(), [](const pair<string, size_t>& s) {
    cout << s.first << " " << s.second << endl;
  });
}

void t10() {
  string last_name;
  string first_name;
  multimap<string, string> names;

  while (cin >> last_name >> first_name) {
    names.emplace(last_name, first_name);
  }

  for (const auto& p : names) {
    cout << p.first << " " << p.second << endl;
  }
}

void t11() {
  const map<string, int> m{{"hello", 1}};
  cout << m.at("hello") << endl;
  // cout << m["hello"] << endl;
  // m.at("hello") = 1;
}

void t12() {
  set<int> s{1, 2, 4, 5, 6};
  cout << (s.lower_bound(3) == s.end()) << " " << *s.lower_bound(3) << endl;
  cout << (s.upper_bound(6) == s.end()) << endl;
  pair<set<int>::iterator, set<int>::iterator> range{s.lower_bound(3),
                                                     s.upper_bound(3)};
  cout << (range.first == range.second) << endl;
}

void t13() {
  multimap<string, string> a{
      {"afw", "fawef"}, {"feaf", "feaff"}, {"feawc", "efvbf"}};
  string s("afw");

  if (a.find(s) != a.end()) {
    a.erase(a.find(s));
  }

  for (auto& i : a) {
    cout << i.first << " " << i.second << endl;
  }
}

void t14() {
  ifstream ifs("../src/ch11/map_file.txt", ifstream::in);
  map<string, string> word_map;
  string key;
  string value;

  while (ifs >> key && getline(ifs, value)) {
    if (value.size() > 1) {
      word_map[key] = value.substr(1);
    } else {
      throw runtime_error("no rule for " + key);
    }
  }

  for (auto& p : word_map) {
    cout << p.first << " " << p.second << endl;
  }

  string line;
  ifstream ifs1("../src/ch11/text.txt", ifstream::in);
  while (getline(ifs1, line)) {
    istringstream iss(line);
    string word;
    while (iss >> word) {
      if (word_map.find(word) != word_map.end()) {
        cout << word_map[word];
      } else {
        cout << word;
      }
      cout << " ";
    }
    cout << endl;
  }
}

void t15() {
  map<string, string> m{{"l8r", "later"}};
  cout << m["l8r"] << endl;
  m.insert({"l8r", "la"});
  cout << m["l8r"] << endl;
}

void t16() {
  ifstream ifs("../src/ch11/map_file.txt", ifstream::in);
  unordered_map<string, string> word_map;
  string key;
  string value;

  while (ifs >> key && getline(ifs, value)) {
    if (value.size() > 1) {
      word_map[key] = value.substr(1);
    } else {
      throw runtime_error("no rule for " + key);
    }
  }

  string line;
  ifstream ifs1("../src/ch11/text.txt", ifstream::in);
  while (getline(ifs1, line)) {
    istringstream iss(line);
    string word;
    while (iss >> word) {
      if (word_map.find(word) != word_map.end()) {
        cout << word_map[word];
      } else {
        cout << word;
      }
      cout << " ";
    }
    cout << endl;
  }
}

void t17() {
  ifstream ifs("../src/ch11/map_file.txt", ifstream::in);
  unordered_map<string, string> word_map;
  string key;
  string value;

  while (ifs >> key && getline(ifs, value)) {
    if (value.size() > 1) {
      word_map[key] = value.substr(1);
    } else {
      throw runtime_error("no rule for " + key);
    }
  }

  cout << "bucket count: " << word_map.bucket_count() << endl
       << "max bucket count: " << word_map.max_bucket_count() << endl
       << "bucket 1 size: " << word_map.bucket_size(1) << endl
       << "l8r in: bucket " << word_map.bucket("l8r") << endl
       << "load factor: " << word_map.load_factor() << endl
       << "max load factor: " << word_map.max_load_factor() << endl;

  word_map.rehash(15);

  cout << endl << "rehashed" << endl;
  cout << "bucket count: " << word_map.bucket_count() << endl
       << "max bucket count: " << word_map.max_bucket_count() << endl
       << "bucket 1 size: " << word_map.bucket_size(1) << endl
       << "l8r in: bucket " << word_map.bucket("l8r") << endl
       << "load factor: " << word_map.load_factor() << endl
       << "max load factor: " << word_map.max_load_factor() << endl;

  word_map.reserve(20);
  cout << endl << "reserve" << endl;
  cout << "bucket count: " << word_map.bucket_count() << endl
       << "max bucket count: " << word_map.max_bucket_count() << endl
       << "bucket 1 size: " << word_map.bucket_size(1) << endl
       << "l8r in: bucket " << word_map.bucket("l8r") << endl
       << "load factor: " << word_map.load_factor() << endl
       << "max load factor: " << word_map.max_load_factor() << endl;

  cout << endl;

  for (size_t i = 0; i < word_map.bucket_count(); ++i) {
    unordered_map<string, string>::const_local_iterator b = word_map.cbegin(i);
    unordered_map<string, string>::const_local_iterator e = word_map.cend(i);

    cout << "bucket: " << i << endl;
    while (b != e) {
      cout << "<" << (*b).first << ", " << (*b).second << ">" << endl;
      ++b;
    }
  }
}

int main(int argc, char* argv[]) {
  // t1();
  // t2();
  // t3();
  // t4();
  // t5();
  // t6();
  // t7();
  // t8();
  // t9();
  // t9();
  // t10();
  // t11();
  // t12();
  // t13();
  // t14();
  // t15();
  // t16();
  t17();
  return 0;
}
