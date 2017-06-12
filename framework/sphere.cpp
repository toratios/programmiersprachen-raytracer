#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
  center_{glm::vec3{0.0f}},
  r_{1.0} {}

Sphere::Sphere(glm::vec3 const& center, float r):
  center_{center},
  r_{r} {}

glm::vec3 const& Sphere::get_center() const{
  return this->center_;
}
    
float Sphere::get_r() const{
  return this->r_;
}

float Sphere::area() const{
  return 4*M_PI*pow(r_,2);
}

float Sphere::volume() const{
  return (4/3)*M_PI*pow(r_,3);
}