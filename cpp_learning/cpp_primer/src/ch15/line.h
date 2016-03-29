#ifndef LINE_H_
#define LINE_H_

#include "point.h"
#include "shape.h"

class Line : public Shape {
 public:
  Line() : Line(Point(), Point()) {}
  Line(Point s, Point e) {
    add(s);
    add(e);
  }
  void draw() const override;
};

#endif /* ifndef LINE_H_ */
