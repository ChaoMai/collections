#include <algorithm>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::fstream;
using std::abs;
using std::string;
using std::vector;

int main() {
  fstream fs;
  fs.open("22_test.txt", fstream::in);

  int c;
  fs >> c;

  for (int i = 0; i < c; ++i) {
    int n, k1, k2, k;
    fs >> n >> k1 >> k2 >> k;

    // read each case
    int w = 0;
    for (int j = 0; j < n; ++j) {
      int tmp;
      fs >> tmp;
      w += tmp;
    }
    cout <<w<<endl;

    // process each case
    if (abs(k1 + k2) <= 1) {
      cout << "CASE #" << i + 1 << ":inf" << endl;
      continue;
    }

    int days = 0;
    while (w <= k) {
      w = (k1 + k2) * w;
      ++days;
    }

    cout << "CASE #" << i + 1 << ":" << days << endl;
  }
  return 0;
}
