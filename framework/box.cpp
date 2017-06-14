#include "box.hpp"
#include <cmath>

Box::Box():
  Shape{"Box"},
  min_{glm::vec3{0.0f}},
  max_{glm::vec3{1.0f}} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
  Shape{"Box"},
  min_{min},
  max_{max} {}
  
Box::Box(glm::vec3 const& min, glm::vec3 const& max, Color const& col, std::string const& name):
  Shape{col, name},
  min_{min},
  max_{max} {}

glm::vec3 const& Box::get_min() const{
  return min_;
}

glm::vec3 const& Box::get_max() const{
  return max_;
}
  
float Box::area() const{
  float x = fabs(max_.x - min_.x);
  float y = fabs(max_.y - min_.y);
  float z = fabs(max_.z - min_.z);
  return (x*y*2+x*z*2+y*z*2);
}

float Box::volume() const{
  float volume = (max_.x - min_.x)*(max_.y - min_.y)*(max_.z - min_.z);
  return fabs(volume);
}

std::ostream& Box::print(std::ostream& os) const{
  Shape::print(os);
  os << "Min: " << "(" << min_.x << "," << min_.y << "," << min_.z << ")" << "\n" 
     << "Min: " << "(" << max_.x << "," << max_.y << "," << max_.z << ")";
  return os; 
}
