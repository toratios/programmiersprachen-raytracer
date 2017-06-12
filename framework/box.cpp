#include "box.hpp"
#include <cmath>

Box::Box():
  min_{glm::vec3{0.0f}},
  max_{glm::vec3{1.0f}} {}
  
Box::Box(glm::vec3 const& min, glm::vec3 const& max):
  min_{min},
  max_{max} {}

  glm::vec3 const& Box::get_min() const{
    return this->min_;
  }

  glm::vec3 const& Box::get_max() const{
    return this->max_;
  }
  
  float Box::area() const{
    return 0;
  }

  float Box::volume() const{
    return 0;
  }