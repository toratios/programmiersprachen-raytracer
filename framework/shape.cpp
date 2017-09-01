#include "shape.hpp"

Shape::Shape():
  mat_{},
  name_{"Shape"},
  world_transformation_{glm::mat4(1.0)},
  world_transformation_inv_{glm::mat4(1.0)},
  translation_{glm::mat4(1.0)},
  rotation_{glm::mat4(1.0)},
  scale_{glm::mat4(1.0)}
  {}

Shape::Shape(std::string const& name):
  mat_{},
  name_{name},
  world_transformation_{glm::mat4(1.0)},
  world_transformation_inv_{glm::mat4(1.0)},
  translation_{glm::mat4(1.0)},
  rotation_{glm::mat4(1.0)},
  scale_{glm::mat4(1.0)}
  {}

Shape::Shape(std::shared_ptr<Material> const& mat, std::string const& name):
  mat_{mat},
  name_{name},
  world_transformation_{glm::mat4(1.0)},
  world_transformation_inv_{glm::mat4(1.0)},
  translation_{glm::mat4(1.0)},
  rotation_{glm::mat4(1.0)},
  scale_{glm::mat4(1.0)}
  {}

Shape::~Shape(){}

std::shared_ptr<Material> const& Shape::get_material() const{
  return mat_;
}

std::string const& Shape::get_name() const{
  return name_;
}

glm::mat4x4 const& Shape::world_transformation() const{
  return world_transformation_;
}

glm::mat4x4 const& Shape::world_transformation_inv() const{
  return world_transformation_inv_;
}

void Shape::scale(glm::vec3 const& scale_vec){
  world_transformation_ = glm::scale(world_transformation_, scale_vec);
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::translate(glm::vec3 const& translate_vec){
  world_transformation_ = glm::translate(world_transformation_, translate_vec);
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate(float angle, glm::vec3 rotate_vec){
  world_transformation_ = glm::rotate(world_transformation_, angle, rotate_vec);
  world_transformation_inv_ = glm::inverse(world_transformation_);
}