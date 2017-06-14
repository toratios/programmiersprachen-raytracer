#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
  Shape{"Sphere"},
  center_{glm::vec3{0.0f}},
  r_{1.0} {}

Sphere::Sphere(glm::vec3 const& center, float r):
  Shape{"Sphere"},
  center_{center},
  r_{r} {}

Sphere::Sphere(glm::vec3 const& center, float r, Color const& col, std::string const& name):
  Shape{col, name},
  center_{center},
  r_{r} {}

glm::vec3 const& Sphere::get_center() const{
  return center_;
}
    
float Sphere::get_r() const{
  return r_;
}

float Sphere::area() const{
  return 4*M_PI*pow(r_,2);
}

float Sphere::volume() const{
  return fabs((4.0/3.0)*M_PI*pow(r_,3));
}