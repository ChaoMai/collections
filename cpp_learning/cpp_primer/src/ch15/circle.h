#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "point.h"
#include "shape.h"

class Circle : public Shape {
 public:
  Circle() : Circle(Point(), 0) {}
  Circle(Point p, int r) : r_(r) { add(p); }
  void draw() const;

 private:
  int r_;
};

#endif /* ifndef CIRCLE_H_ */
