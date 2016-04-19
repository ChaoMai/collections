#include <functional>
#include <iostream>

using std::cout;
using std::endl;
using std::greater;
using std::less;

template <typename T, typename F = less<T>>
int compare_default(const T &v1, const T &v2, F f = F()) {
  if (f(v1, v2)) {
    return -1;
  }

  if (f(v2, v1)) {
    return 1;
  }

  return 0;
}

int main() {
  // cout << greater<int>()(1, 4) << endl;
  // cout << compare_default(1, 4, greater<int>()) << endl;
  // cout << compare_default<int, greater<int>>(1, 4) << endl;
  cout << compare_default<int, bool (*)(int, int)>(1, 4) << endl;
  // cout << compare_default<int, bool (*)(int, int)>(1, 4, [](int, int) {
  // return true;
  // }) << endl;
}
