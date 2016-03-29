#ifndef UTIL_H_
#define UTIL_H_

#include <algorithm>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::for_each;
using std::vector;

inline void print1D(const vector<int>& arr) {
  for_each(arr.begin(), arr.end(), [](int i) { cout << i << " "; });
}

#endif /* ifndef UTIL_H_ */
