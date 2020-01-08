#ifndef POINT_H_
#define POINT_H_

#include <iostream>

struct Point {
  friend std::ostream& operator<<(std::ostream& os, const Point& p);
  Point() : Point(0, 0) {}
  Point(int x, int y) : x_(x), y_(y) {}

  int x_ = 0;
  int y_ = 0;
};

std::ostream& operator<<(std::ostream& os, const Point& p);

#endif /* ifndef POINT_H_ */
