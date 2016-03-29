#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "point.h"
#include "shape.h"

class Rectangle : public Shape {
 public:
  Rectangle() : Rectangle(Point(), 0, 0) {}
  Rectangle(Point p, int l, int w) : l_(l), w_(w) { add(p); }
  void draw() const override;

 private:
  int l_ = 0;
  int w_ = 0;
};

#endif /* ifndef RECTANGLE_H_ */
