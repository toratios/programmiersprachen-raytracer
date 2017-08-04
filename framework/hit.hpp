#ifndef HIT_HPP
#define HIT_HPP


#include "shape.hpp"

class Shape;

struct Hit{
  Hit();
  Hit(bool hit, float t, glm::vec3 const& intersect, 
      glm::vec3 const& normal, std::shared_ptr<Shape> shape);
  Hit(Hit const& hit_copy);

  bool hit_;
  float t_;
  glm::vec3 intersection_;
  glm::vec3 normal_;
  std::shared_ptr<Shape> shape_;
};

#endif