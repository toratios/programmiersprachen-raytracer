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
  glm::mat4 S;
  S[0] = glm::vec4{scale_vec.x, 0.0f, 0.0f, 0.0f};
  S[1] = glm::vec4{0.0f, scale_vec.y, 0.0f, 0.0f};
  S[2] = glm::vec4{0.0f, 0.0f, scale_vec.z, 0.0f};
  S[3] = glm::vec4{0.0f, 0.0f, 0.0f, 1.0f};
  scale_ = S;
  world_transformation_ = translation_ * rotation_ * scale_;
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::translate(glm::vec3 const& translate_vec){
  glm::mat4 T;
  T[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
  T[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
  T[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
  T[3] = glm::vec4{translate_vec.x, translate_vec.y, translate_vec.z, 1.0f};
  translation_ = T;
  world_transformation_ = translation_ * rotation_ * scale_;
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::rotate(float angle, glm::vec3 rotate_vec){
  float angle_rad = (angle*3.1415926535897f)/180.0f;
  glm::mat4x4 R = glm::rotate(glm::mat4(1.0), angle_rad, rotate_vec);
  rotation_ = R;
  world_transformation_ = translation_ * rotation_ * scale_;
  world_transformation_inv_ = glm::inverse(world_transformation_);
}