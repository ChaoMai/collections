#include "point.h"

#include <iostream>

using std::ostream;

ostream& operator<<(ostream& os, const Point& p) {
  os << "(" << p.x_ << ", " << p.y_ << ")";
  return os;
}
