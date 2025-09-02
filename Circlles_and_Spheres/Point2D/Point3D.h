#pragma once 

#include "Point.h"

class CPoint3D : public CPoint {
  int _z;
public:
  CPoint3D(int x = 0, int y = 0, int z = 0);
  CPoint3D(const CPoint3D& other);

  int get_z() const {
    return _z;
  }
};