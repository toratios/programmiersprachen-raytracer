#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
  Shape{"Sphere"},
  center_{glm::vec3{0.0f}},
  r_{1.0} {std::cout << "ctor class Sphere\n";}

Sphere::Sphere(glm::vec3 const& center, float r):
  Shape{"Sphere"},
  center_{center},
  r_{r} {std::cout << "ctor class Sphere\n";}

Sphere::Sphere(glm::vec3 const& center, float r, Color const& col, std::string const& name):
  Shape{col, name},
  center_{center},
  r_{r} {std::cout << "ctor class Sphere\n";}

Sphere::~Sphere(){
  std::cout << "dtor class Sphere\n";
}

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

std::ostream& Sphere::print(std::ostream& os) const{
  Shape::print(os);
  os << "Center: " << "(" << center_.x << "," << center_.y << "," << center_.z << ")" 
     << "\nRadius: " << r_ << "\n";
  return os; 
}

bool Sphere::intersect(Ray const& ray, float& t){
  auto result = glm::intersectRaySphere(ray.origin, ray.direction, center_, r_ * r_, t);
  return result;
}