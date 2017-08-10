#include "shape.hpp"

Shape::Shape():
  mat_{},
  name_{"Shape"},
  world_transformation_{glm::mat4{1.0}},
  world_transformation_inv_{glm::inverse(glm::mat4(world_transformation_))},
  world_transformation_inv_transp_{glm::transpose(glm::mat4(world_transformation_inv_))},
  transf_{false}
  {}

Shape::Shape(std::string const& name):
  mat_{},
  name_{name},
  world_transformation_{glm::mat4{1.0}},
  world_transformation_inv_{glm::inverse(glm::mat4(world_transformation_))},
  world_transformation_inv_transp_{glm::transpose(glm::mat4(world_transformation_inv_))},
  transf_{false}
  {}

Shape::Shape(std::shared_ptr<Material> const& mat, std::string const& name):
  mat_{mat},
  name_{name},
  world_transformation_{glm::mat4{1.0}},
  world_transformation_inv_{glm::inverse(glm::mat4(world_transformation_))},
  world_transformation_inv_transp_{glm::transpose(glm::mat4(world_transformation_inv_))},
  transf_{false}
  {}

Shape::~Shape(){}

std::shared_ptr<Material> const& Shape::get_material() const{
  return mat_;
}

std::string const& Shape::get_name() const{
  return name_;
}

std::ostream& Shape::print(std::ostream& os) const{
  os << "Name: " << name_ << "\n" << "Material: \n" << mat_ ;
  return os; 
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
  return s.print(os);
}



glm::mat4 const& Shape::get_transf() const
{
  return world_transformation_;
}

glm::mat4 const& Shape::get_inv() const
{
  return world_transformation_inv_;
}

glm::mat4 const& Shape::get_inv_transp() const
{
  return world_transformation_inv_transp_;
}

bool Shape::is_transf() const
{
  return transf_;
}


void Shape::scale(glm::vec3 const& scale_vec)
{
  world_transformation_ = world_transformation_ * glm::scale(glm::mat4(), scale_vec);
  world_transformation_inv_ = glm::inverse(glm::mat4(world_transformation_));
  world_transformation_inv_transp_ = glm::transpose(glm::mat4(world_transformation_inv_));
  transf_ = true;
}

void Shape::rotate(float angle, glm::vec3 const& rotation_vec)
{
  angle *= 0.017453292519943f;
  world_transformation_ = world_transformation_ * glm::rotate(glm::mat4(), angle, rotation_vec);
  world_transformation_inv_ = glm::inverse(glm::mat4(world_transformation_));
  world_transformation_inv_transp_ = glm::transpose(glm::mat4(world_transformation_inv_));
  transf_ = true;
}

void Shape::translate(glm::vec3 const& transl_vec)
{
  world_transformation_ = world_transformation_ * glm::translate(glm::mat4(), transl_vec);
  world_transformation_inv_ = glm::inverse(glm::mat4(world_transformation_));
  world_transformation_inv_transp_ = glm::transpose(glm::mat4(world_transformation_inv_));
  transf_ = true;
}