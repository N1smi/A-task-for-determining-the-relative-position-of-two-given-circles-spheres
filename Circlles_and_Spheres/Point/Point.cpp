#include "Point.h"

CPoint::CPoint(int x, int y) {
  _x = x;
  _y = y;
}

CPoint::CPoint(const CPoint& other) {
  _x = other._x;
  _y = other._y;
}