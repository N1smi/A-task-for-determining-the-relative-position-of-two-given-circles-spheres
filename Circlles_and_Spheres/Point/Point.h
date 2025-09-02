#pragma once 

class CPoint{
  int _x;
  int _y;
public:
  CPoint(int x = 0, int y = 0);

  CPoint(const CPoint& other);

  void set_x(int x) {
    _x = x;
  }

  void set_y(int y) {
    _y= y;
  }

  int get_x() const {
    return _x;
  }

  int get_y() const {
    return _y;
  }
};