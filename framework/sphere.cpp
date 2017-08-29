#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
  Shape{"Sphere"},
  center_{glm::vec3{0.0f}},
  r_{1.0} {/*std::cout << "ctor class Sphere\n";*/}

Sphere::Sphere(glm::vec3 const& center, float r):
  Shape{"Sphere"},
  center_{center},
  r_{r} {/*std::cout << "ctor class Sphere\n";*/}

Sphere::Sphere(glm::vec3 const& center, float r, std::shared_ptr<Material> const& mat, std::string const& name):
  Shape{mat, name},
  center_{center},
  r_{r} {/*std::cout << "ctor class Sphere\n";*/}

Sphere::~Sphere(){/*
  std::cout << "dtor class Sphere\n";*/
}

glm::vec3 const& Sphere::get_center() const{
  return center_;
}
    
float Sphere::get_r() const{
  return r_;
}
/*
float Sphere::area() const{
  return 4*M_PI*pow(r_,2);
}

float Sphere::volume() const{
  return fabs((4.0/3.0)*M_PI*pow(r_,3));
}*/

std::ostream& Sphere::print(std::ostream& os) const{
  Shape::print(os);
  os << "Center: " << "(" << center_.x << "," << center_.y << "," << center_.z << ")" 
     << "\nRadius: " << r_ << "\n";
  return os; 
}

Hit Sphere::intersect(Ray const& inray){
/*
  Hit spherehit;
  Ray ray;
  ray.origin = inray.origin;
  ray.direction = glm::normalize(inray.direction);
  spherehit.hit_ = glm::intersectRaySphere(ray.origin, ray.direction, center_, r_ * r_, spherehit.t_);
  
  if(spherehit.hit_ == true){
    spherehit.intersection_ = ray.origin + ray.direction * spherehit.t_;
    spherehit.normal_ = glm::normalize(spherehit.intersection_ - center_);
    spherehit.shape_ = this;
  }

  return spherehit;*/

  Hit sphere_hit;

  Ray ray
  {
    inray.origin,

    glm::normalize(inray.direction)
  };

  float t0;
  float t1;

  glm::vec3 L = center_ - ray.origin;

  float tca = glm::dot(L, ray.direction);

  float d2 = glm::dot(L, L) - tca * tca;

  if(d2 > (r_ * r_))
  {
    return sphere_hit;
  }

  float thc = sqrt((r_ * r_) - d2);

  t0 = tca - thc;

  t1 = tca + thc;

  if(t0 > t1)
  {
    std::swap(t0, t1);
  }

  if(t0 < 0)
  {
    t0 = t1;

    if(t0 < 0)
    {
      return sphere_hit;
    }
  }

  sphere_hit.hit_ = true;
  sphere_hit.t_ = t0;
  sphere_hit.shape_ = this;
  sphere_hit.intersection_ = ray.origin + ray.direction * sphere_hit.t_;
  sphere_hit.normal_ = glm:: normalize(sphere_hit.intersection_ - center_);

  return sphere_hit;
}