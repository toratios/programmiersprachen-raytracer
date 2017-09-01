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

Sphere::Sphere(glm::vec3 const& center, float r, std::shared_ptr<Material> const& mat, std::string const& name):
  Shape{mat, name},
  center_{center},
  r_{r} {}

Sphere::~Sphere(){}

glm::vec3 const& Sphere::get_center() const
{
  return center_;
}
    
float Sphere::get_r() const
{
  return r_;
}

Hit Sphere::intersect(Ray const& inray)
{
  Hit sphere_hit;

  Ray ray
  {
    inray.origin,

    glm::normalize(inray.direction)

  };

  /*if(transformed()){
    ray = transformRay(world_transformation_inv(), ray);
  }*/

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
  sphere_hit.normal_ = glm::normalize(sphere_hit.intersection_ - center_);
    //sphere_hit.intersection_ = glm::vec3(world_transformation()* glm::vec4(sphere_hit.intersection_, 1));
  sphere_hit.normal_ = glm::vec3(glm::mat3(glm::transpose(world_transformation_inv())) * sphere_hit.normal_);    

  return sphere_hit;
}