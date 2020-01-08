#include "quote.h"

#include <iostream>

using std::cout;
using std::endl;

void Quote::debug() const {
  cout << "bookNo: " << bookNo << endl << "price: " << price << endl;
}
