#include "Point3D.h"

CPoint3D::CPoint3D(int x, int y, int z) : CPoint(x, y), _z(z) {}

CPoint3D::CPoint3D(const CPoint3D& other) : CPoint(other.get_x(), other.get_y()), _z(other._z) {}