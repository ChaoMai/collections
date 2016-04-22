#include <functional>
#include <iostream>

using std::cout;
using std::endl;
using std::greater;
using std::less;

template <typename T>
class F;

template <typename T>
void pf1(F<T>);

void pf2(F<int>);

template <typename T>
void pf3(F<T>);

template <typename T>
class F {
  friend void pf1(F);
  // template <typename PF1T>
  // friend void pf1(F<PF1T>);
  friend void pf2(F);
  friend void pf3<T>(F);

 public:
  F() = default;

 private:
  T t = 100;
};

template <typename T>
void pf1(F<T> f) {
  cout << f.t << endl;
}

void pf2(F<int> f) { cout << f.t << endl; }

template <typename T>
void pf3(F<T> f) {
  cout << f.t << endl;
}

int main() {
  F<int> f;
  pf1(f);  // linker: cannot find definition
  // pf1<int>(f); // compiler: cannot access
  pf2(f);  // ok
  pf3(f);
  pf3<int>(f);
}
