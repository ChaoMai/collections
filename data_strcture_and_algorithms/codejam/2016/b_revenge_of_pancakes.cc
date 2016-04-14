#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::min;
using std::string;
using std::unordered_set;

bool check(const string&);
int flip(unordered_set<string>&, string&);

int main() {
  ifstream ifs("B-input.in", ifstream::in);

  if (!ifs) {
    cout << "open input failed" << endl;
  }

  int n;
  ifs >> n;

  unordered_set<string> set;

  for (int i = 1; i <= n; ++i) {
    set.clear();

    string tmp;
    ifs >> tmp;

    set.insert(tmp);

    cout << "case #" << i << ": " << flip(set, tmp) << endl;
  }

  return 0;
}

bool check(const string& pancake) {
  for (auto c : pancake) {
    if (c == '-') {
      return false;
    }
  }

  return true;
}

int flip(unordered_set<string>& set, string& pancake) {
  if (check(pancake)) {
    return 0;
  }

  int ret = INT_MAX;

  for (string::size_type i = 0; i < pancake.size(); ++i) {
  }

  return 1;
}
