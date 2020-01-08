#ifndef SHAPE_H_
#define SHAPE_H_

#include <cstddef>
#include <vector>

#include "point.h"

class Shape {
 public:
  Shape() = default;
  virtual ~Shape() = default;

  virtual void draw() const = 0;
  virtual void move(int dx, int dy);

 protected:
  Point& operator[](std::size_t n) { return points_[n]; }
  const Point& operator[](std::size_t n) const { return points_[n]; }
  void add(Point p) { points_.push_back(p); }
  std::size_t number_of_points() const { return points_.size(); }

 private:
  std::vector<Point> points_;
};

#endif /* ifndef SHAPE_H_ */
