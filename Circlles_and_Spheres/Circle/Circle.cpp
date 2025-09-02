#include "Circle.h"

Circle::Circle() : _center(0, 0), _rad(0) {}

Circle::Circle(const Circle& other) : _center(other._center), _rad(other._rad) {}

Circle::Circle(CPoint center, int rad) : _center(center), _rad(rad) {}

