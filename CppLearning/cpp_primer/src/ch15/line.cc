#include "line.h"

#include <iostream>

using std::cout;
using std::endl;

void Line::draw() const {
  cout << "Line, start at " << (*this)[0] << ", end at " << (*this)[1] << endl;
}
