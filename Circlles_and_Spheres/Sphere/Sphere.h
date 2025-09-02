#pragma once 
#include "Point.h"
#include "Point3D.h"
#include "Circle.h"

class Sphere : public Circle{
  CPoint3D _center;
public:
  Sphere() : Circle(), _center(0, 0, 0) {}
  Sphere(CPoint3D center, int rad)
    : Circle(CPoint(center.get_x(), center.get_y()), rad), _center(center) {
  }

  int get_z() const override { return _center.get_z(); };
};