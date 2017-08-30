#include "shape.hpp"

Shape::Shape():
  mat_{},
  name_{"Shape"},
  world_transformation_{glm::mat4x4 {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0}},
  world_transformation_inv_{glm::mat4x4 {1.0, 0.0, 0.0, 0.0,
                                         0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0}}
  {}

Shape::Shape(std::string const& name):
  mat_{},
  name_{name},
  world_transformation_{glm::mat4x4 {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0}},
  world_transformation_inv_{glm::mat4x4 {1.0, 0.0, 0.0, 0.0,
                                         0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0}}
  {}

Shape::Shape(std::shared_ptr<Material> const& mat, std::string const& name):
  mat_{mat},
  name_{name},
  world_transformation_{glm::mat4x4 {1.0, 0.0, 0.0, 0.0,
                                     0.0, 1.0, 0.0, 0.0,
                                     0.0, 0.0, 1.0, 0.0,
                                     0.0, 0.0, 0.0, 1.0}},
  world_transformation_inv_{glm::mat4x4 {1.0, 0.0, 0.0, 0.0,
                                         0.0, 1.0, 0.0, 0.0,
                                         0.0, 0.0, 1.0, 0.0,
                                         0.0, 0.0, 0.0, 1.0}}
  {}

Shape::~Shape(){}

std::shared_ptr<Material> const& Shape::get_material() const{
  return mat_;
}

std::string const& Shape::get_name() const{
  return name_;
}

bool Shape::transformed() const{
  return transformed_;
}

glm::mat4x4 const& Shape::world_transformation() const{
  return world_transformation_;
}

glm::mat4x4 const& Shape::world_transformation_inv() const{
  return world_transformation_inv_;
}