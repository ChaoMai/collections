#include "circle.h"

#include <iostream>

using std::cout;
using std::endl;

void Circle::draw() const {
  cout << "Circle, at " << (*this)[0] << ", r is " << r_ << endl;
}
