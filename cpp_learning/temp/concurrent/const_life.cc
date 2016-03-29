#include <iostream>
#include <string>

using namespace std;

class str {
  friend ostream& print(const str& s);

 public:
  str(const char* s) : s_(s) { cout << "cons" << endl; }

 private:
  string s_;
};

ostream& print(const str& s) { cout << s.s_; }

// const string& Func() { return "123"; }
str Func() { return "123"; }

int main() {
  str s = Func();
  print(s);
  return 0;
}
