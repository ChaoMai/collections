#include "rectangle.h"

#include <iostream>

using std::cout;
using std::endl;

void Rectangle::draw() const {
  cout << "Rectangle, up left point is " << (*this)[0] << ", Lenght " << l_
       << ", Width " << w_ << endl;
}
