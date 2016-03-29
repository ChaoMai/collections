#ifndef INPUTSTRING_H_
#define INPUTSTRING_H_

#include <iostream>
#include <string>

class InputString {
 public:
  InputString(std::istream& i = std::cin) : is(i){};
  std::string operator()() {
    std::string tmp;
    if (getline(is, tmp)) {
      return tmp;
    } else {
      return std::string();
    }
  }

 private:
  std::istream& is;
};

#endif /* ifndef INPUTSTRING_H_ */
