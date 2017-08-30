#include "shape.hpp"

Shape::Shape():
  mat_{},
  name_{"Shape"}
  {}

Shape::Shape(std::string const& name):
  mat_{},
  name_{name}
  {}

Shape::Shape(std::shared_ptr<Material> const& mat, std::string const& name):
  mat_{mat},
  name_{name}
  {}

Shape::~Shape(){}

std::shared_ptr<Material> const& Shape::get_material() const{
  return mat_;
}

std::string const& Shape::get_name() const{
  return name_;
}




