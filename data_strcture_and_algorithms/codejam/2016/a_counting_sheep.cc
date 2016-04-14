#include <fstream>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::to_string;

unsigned long long process(unsigned long long);

int main() {
  // ifstream ifs("A-small-attempt0.in", ifstream::in);
  ifstream ifs("A-large.in", ifstream::in);
  // ifstream ifs("A-input.txt", ifstream::in);

  if (!ifs) {
    cout << "open input failed" << endl;
  }

  int n;
  ifs >> n;

  for (int i = 1; i <= n; ++i) {
    unsigned long long c;
    ifs >> c;
    unsigned long long ret = process(c);
    cout << "case #" << i << ": " << (ret == 0 ? "INSOMNIA" : to_string(ret))
         << endl;
  }

  return 0;
}

unsigned long long process(unsigned long long c) {
  if (c == 0) {
    return 0;
  }

  unsigned long long mul_c = 0;
  int count = 0x3ff;
  int prev_count;

  while (count != 0) {
    mul_c += c;

    string tmp(to_string(mul_c));

    prev_count = count;
    for (string::size_type i = 0; i < tmp.size(); ++i) {
      int bit = 1 << (tmp[i] - '0');
      if ((count & bit) != 0) {
        count ^= bit;
      }
    }
  }

  return mul_c;
}
