#include "shape.h"

#include <algorithm>

#include "point.h"

using std::for_each;

void Shape::move(int dx, int dy) {
  for_each(points_.begin(), points_.end(), [dx, dy](Point& p) {
    p.x_ += dx;
    p.y_ += dy;
  });
}
