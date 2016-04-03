#include "hex_multiply.h"

#include <cstddef>
#include <cstring>
#include <string>

#ifndef NDEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

using std::string;

int get_int(char ch) {
  if (isdigit(ch)) {
    return ch - '0';
  } else {
    return tolower(ch) - 'a' + 10;
  }
}

char to_hex(int num) {
  if (0 <= num && num <= 9) {
    return static_cast<char>(num + '0');
  } else {
    return static_cast<char>(num - 10 + 'a');
  }
}

string hex_multipy(const char* ele1, const char* ele2) {
  bool isNeg = false;

  if (ele1[0] != ele2[0]) {
    isNeg = true;
  }

  if (ele1[0] == '-') {
    ++ele1;
  }

  if (ele2[0] == '-') {
    ++ele2;
  }

  size_t len1 = strlen(ele1);
  size_t len2 = strlen(ele2);

  if (len1 <= 2 || len2 <= 2 || tolower(ele1[1]) != 'x' ||
      tolower(ele2[1]) != 'x') {
    return string();
  }

  string ret(len1 + len2 - 4, '0');
  ele1 += 2;
  ele2 += 2;

  for (int i = len1 - 3; i >= 0; --i) {
    int carry = 0;
    for (int j = len2 - 3; j >= 0; --j) {
      int tmp =
          get_int(ret[i + j + 1]) + get_int(ele1[i]) * get_int(ele2[j]) + carry;
      ret[i + j + 1] = to_hex(tmp % 16);
      carry = tmp / 16;
    }
    ret[i] = to_hex(get_int(ret[i]) + carry);
  }

  auto pos = ret.find_first_not_of('0');
  if (string::npos != pos) {
    return isNeg ? "-0x" + ret.substr(pos) : "0x" + ret.substr(pos);
  }

  return string("0");
}
