#include "shape.hpp"

Shape::Shape():
  color_{Color{1.0,1.0,1.0}},
  name_{"Shape"} {}

Shape::Shape(std::string const& name):
  color_{Color{1.0,1.0,1.0}},
  name_{name} {}

Shape::Shape(Color const& col, std::string const& name):
  color_{col},
  name_{name} {}

Color const& Shape::get_color() const{
  return color_;
}

std::string const& Shape::get_name() const{
  return name_;
}

std::ostream& Shape::print(std::ostream& os) const{
  os << "Name: " << name_ << "\n" << "Color: " << color_ ;
  return os; 
}

std::ostream& operator<<(std::ostream& os, Shape const& s){
  return s.print(os);
}