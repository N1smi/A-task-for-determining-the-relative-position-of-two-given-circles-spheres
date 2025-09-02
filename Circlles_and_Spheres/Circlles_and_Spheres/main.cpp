#include <iostream>
#include <windows.h>
#include "Point.h"
#include "Circle.h"
#include "Point3D.h"
#include "Sphere.h"

void set_color(int text_color, int bg_color) {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hConsole, (bg_color << 4) | text_color);
}

namespace TestSystem {
  int count_success = 0, count_failed = 0;

  void start_test(bool(*test)(), const char* name_of_test) {
    set_color(2, 0);
    std::cout << "[ RUN      ]";
    set_color(7, 0);
    std::cout << name_of_test << std::endl;

    bool status = test();

    if (status == true) {
      set_color(2, 0);
      std::cout << "[       OK ]" << std::endl;
      count_success++;
    }
    else {
      set_color(4, 0);
      std::cout << "[  FAILED  ]" << std::endl;
      count_failed++;
    }
    set_color(7, 0);
  }

  template <class T>
  bool check(const T& expected, const T& actual) {
    if (expected == actual) {
      return true;
    }
    else {
      std::cerr << "Expected result is " << expected
        << ", but actual is " << actual << "." << std::endl;
      return false;
    }
  }

  void print_init_info() {
    set_color(2, 0);
    std::cout << "[==========] " << std::endl;
    set_color(7, 0);
  }

  void print_final_info() {
    set_color(2, 0);
    std::cout << "[==========] ";
    set_color(7, 0);
    std::cout << count_success + count_failed << " test"
      << (count_success + count_failed > 1 ? "s" : "") << " ran." << std::endl;
    set_color(2, 0);
    std::cout << "[  PASSED  ] ";
    set_color(7, 0);
    std::cout << count_success << " test"
      << (count_success > 1 ? "s" : "") << std::endl;
    if (count_failed > 0) {
      set_color(4, 0);
      std::cout << "[  FAILED  ] ";
      set_color(7, 0);
      std::cout << count_failed << " test"
        << (count_failed > 1 ? "s." : ".") << std::endl;
    }
  }
};  // namespace TestSystem

bool test_1_create_default_point() {
  CPoint point;

  bool result = (TestSystem::check(0, point.get_x())
    && TestSystem::check(0, point.get_y()));

  return result;
}

bool test_2_create_point_with_params() {
  CPoint point(5, 10);
  bool result = (TestSystem::check(5, point.get_x())
    && TestSystem::check(10, point.get_y()));

  return result;
}

bool test_3_create_point_copy_constructor() {
  CPoint original(7, 3);
  CPoint copy(original);
  bool result = (TestSystem::check(7, copy.get_x())
    && TestSystem::check(3, copy.get_y()));
  return result;
}

bool test_4_create_default_circle() {
  Circle circle;
  bool result = (TestSystem::check(0, circle.get_x())
    && TestSystem::check(0, circle.get_y())
    && TestSystem::check(0, circle.get_rad()));
  return result;
}

bool test_5_create_circle_with_params() {
  CPoint center(3, 4);
  Circle circle(center, 5);
  bool result = (TestSystem::check(3, circle.get_x())
    && TestSystem::check(4, circle.get_y())
    && TestSystem::check(5, circle.get_rad()));
  return result;
}

bool test_6_create_circle_copy_constructor() {
  CPoint center(1, 2);
  Circle original(center, 3);
  Circle copy(original);
  bool result = (TestSystem::check(1, copy.get_x())
    && TestSystem::check(2, copy.get_y())
    && TestSystem::check(3, copy.get_rad()));
  return result;
}

bool test_7_create_circle_direct_coords() {
  Circle circle(CPoint(8, 6), 10);
  bool result = (TestSystem::check(8, circle.get_x())
    && TestSystem::check(6, circle.get_y())
    && TestSystem::check(10, circle.get_rad()));
  return result;
}

bool test_8_circles_no_intersection() {
  Circle c1(CPoint(0, 0), 2);
  Circle c2(CPoint(8, 0), 3);
  loc result = Circle::location_of_the_circles(c1, c2);
  return TestSystem::check(without_interaction, result);
}

bool test_9_circles_intersection() {
  Circle c1(CPoint(0, 0), 5);
  Circle c2(CPoint(6, 0), 4);
  loc result = Circle::location_of_the_circles(c1, c2);
  return TestSystem::check(interaction, result);
}

bool test_10_circles_internal_touch() {
  Circle c1(CPoint(0, 0), 5);
  Circle c2(CPoint(2, 0), 3);
  loc result = Circle::location_of_the_circles(c1, c2);
  return TestSystem::check(touch_in, result);
}

bool test_11_circles_external_touch() {
  Circle c1(CPoint(0, 0), 5);
  Circle c2(CPoint(8, 0), 3);
  loc result = Circle::location_of_the_circles(c1, c2);
  return TestSystem::check(touch_out, result);
}

bool test_12_circles_one_inside_another() {
  Circle c1(CPoint(0, 0), 8);
  Circle c2(CPoint(2, 0), 3);
  loc result = Circle::location_of_the_circles(c1, c2);
  return TestSystem::check(entry, result);
}

bool test_13_identical_circles() {
  Circle c1(CPoint(0, 0), 5);
  Circle c2(CPoint(0, 0), 5);
  loc result = Circle::location_of_the_circles(c1, c2);
  return TestSystem::check(coincidence, result);
}

bool test_14_cpoint3d_default_constructor() {
  CPoint3D point;
  bool result = TestSystem::check(0, point.get_x()) &&
    TestSystem::check(0, point.get_y()) &&
    TestSystem::check(0, point.get_z());
  return result;
}

bool test_15_cpoint3d_param_constructor() {
  CPoint3D point(5, 10, 15);
  bool result = TestSystem::check(5, point.get_x()) &&
    TestSystem::check(10, point.get_y()) &&
    TestSystem::check(15, point.get_z());
  return result;
}

bool test_16_cpoint3d_copy_constructor() {
  CPoint3D original(7, 3, 12);
  CPoint3D copy(original);
  bool result = TestSystem::check(7, copy.get_x()) &&
    TestSystem::check(3, copy.get_y()) &&
    TestSystem::check(12, copy.get_z());
  return result;
}

bool test_17_sphere_default_constructor() {
  Sphere sphere;
  bool result = TestSystem::check(0, sphere.get_x()) &&
    TestSystem::check(0, sphere.get_y()) &&
    TestSystem::check(0, sphere.get_z()) &&
    TestSystem::check(0, sphere.get_rad());
  return result;
}

bool test_18_sphere_param_constructor() {
  CPoint3D center(5, 10, 15);
  Sphere sphere(center, 7);
  bool result = TestSystem::check(5, sphere.get_x()) &&
    TestSystem::check(10, sphere.get_y()) &&
    TestSystem::check(15, sphere.get_z()) &&
    TestSystem::check(7, sphere.get_rad());
  return result;
}

bool test_19_sphere_copy_constructor() {
  CPoint3D center(3, 6, 9);
  Sphere original(center, 12);
  Sphere copy(original);
  bool result = TestSystem::check(3, copy.get_x()) &&
    TestSystem::check(6, copy.get_y()) &&
    TestSystem::check(9, copy.get_z()) &&
    TestSystem::check(12, copy.get_rad());
  return result;
}

bool test_20_sphere_direct_constructor() {
  Sphere sphere(CPoint3D(8, 4, 2), 10);
  bool result = TestSystem::check(8, sphere.get_x()) &&
    TestSystem::check(4, sphere.get_y()) &&
    TestSystem::check(2, sphere.get_z()) &&
    TestSystem::check(10, sphere.get_rad());
  return result;
}

bool test_21_sphere_no_intersection() {
  Sphere s1(CPoint3D(0, 0, 0), 2);
  Sphere s2(CPoint3D(10, 0, 0), 3);
  loc result = Circle::location_of_the_circles(s1, s2);
  return TestSystem::check(without_interaction, result);
}

bool test_22_sphere_external_touch() {
  Sphere s1(CPoint3D(0, 0, 0), 5);
  Sphere s2(CPoint3D(8, 0, 0), 3);
  loc result = Circle::location_of_the_circles(s1, s2);
  return TestSystem::check(touch_out, result);
}

bool test_23_sphere_intersection() {
  Sphere s1(CPoint3D(0, 0, 0), 5);
  Sphere s2(CPoint3D(6, 0, 0), 4);
  loc result = Circle::location_of_the_circles(s1, s2);
  return TestSystem::check(interaction, result);
}

bool test_24_sphere_internal_touch() {
  Sphere s1(CPoint3D(0, 0, 0), 5);
  Sphere s2(CPoint3D(2, 0, 0), 3);
  loc result = Circle::location_of_the_circles(s1, s2);
  return TestSystem::check(touch_in, result);
}

bool test_25_sphere_one_inside_another() {
  Sphere s1(CPoint3D(0, 0, 0), 8);
  Sphere s2(CPoint3D(2, 0, 0), 3);
  loc result = Circle::location_of_the_circles(s1, s2);
  return TestSystem::check(entry, result);
}

bool test_26_sphere_identical() {
  Sphere s1(CPoint3D(0, 0, 0), 5);
  Sphere s2(CPoint3D(0, 0, 0), 5);
  loc result = Circle::location_of_the_circles(s1, s2);
  return TestSystem::check(coincidence, result);
}

int main() {
  set_color(6, 0);
  std::cout << "Circles_and_Spheres test" << std::endl;
  set_color(7, 0);

  TestSystem::start_test(test_1_create_default_point,
    " TVector.test_1_create_default_point");
  TestSystem::start_test(test_2_create_point_with_params,
    " TVector.test_2_create_point_with_params");
  TestSystem::start_test(test_3_create_point_copy_constructor,
    " TVector.test_3_create_point_copy_constructor");
  TestSystem::start_test(test_4_create_default_circle,
    " TVector.test_4_create_default_circle");
  TestSystem::start_test(test_5_create_circle_with_params,
    " TVector.test_5_create_circle_with_params");
  TestSystem::start_test(test_6_create_circle_copy_constructor,
    " TVector.test_6_create_circle_copy_constructor");
  TestSystem::start_test(test_7_create_circle_direct_coords,
    " TVector.test_7_create_circle_direct_coords");
  TestSystem::start_test(test_8_circles_no_intersection,
    " TVector.test_8_circles_no_intersection");
  TestSystem::start_test(test_9_circles_intersection,
    " TVector.test_9_circles_intersection");
  TestSystem::start_test(test_10_circles_internal_touch,
    " TVector.test_10_circles_internal_touch");
  TestSystem::start_test(test_11_circles_external_touch,
    " TVector.test_11_circles_external_touch");
  TestSystem::start_test(test_12_circles_one_inside_another,
    " TVector.test_12_circles_one_inside_another");
  TestSystem::start_test(test_13_identical_circles,
    " TVector.test_13_identical_circles");
  TestSystem::start_test(test_14_cpoint3d_default_constructor,
    " TVector.test_14_cpoint3d_default_constructor");
  TestSystem::start_test(test_15_cpoint3d_param_constructor,
    " TVector.test_15_cpoint3d_param_constructor");
  TestSystem::start_test(test_16_cpoint3d_copy_constructor,
    " TVector.test_16_cpoint3d_copy_constructor");
  TestSystem::start_test(test_17_sphere_default_constructor,
    " TVector.test_17_sphere_default_constructor");
  TestSystem::start_test(test_18_sphere_param_constructor,
    " TVector.test_18_sphere_param_constructor");
  TestSystem::start_test(test_19_sphere_copy_constructor,
    " TVector.test_19_sphere_copy_constructor");
  TestSystem::start_test(test_20_sphere_direct_constructor,
    " TVector.test_20_sphere_direct_constructor");
  TestSystem::start_test(test_21_sphere_no_intersection,
    " TVector.test_21_sphere_no_intersection");
  TestSystem::start_test(test_22_sphere_external_touch,
    " TVector.test_22_sphere_external_touch");
  TestSystem::start_test(test_23_sphere_intersection,
    " TVector.test_23_sphere_intersection");
  TestSystem::start_test(test_24_sphere_internal_touch,
    " TVector.test_24_sphere_internal_touch");
  TestSystem::start_test(test_25_sphere_one_inside_another,
    " TVector.test_25_sphere_one_inside_another");
  TestSystem::start_test(test_26_sphere_identical,
    " TVector.test_26_sphere_identical");

  TestSystem::print_final_info();
  TestSystem::count_success = 0;
  TestSystem::count_failed = 0;
  std::cout << std::endl;
}