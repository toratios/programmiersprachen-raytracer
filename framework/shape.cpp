#include "shape.hpp"

Shape::Shape():
  color_{Color{1.0,1.0,1.0}},
  name_{"Shape"} {std::cout << "ctor class Shape\n";}

Shape::Shape(std::string const& name):
  color_{Color{1.0,1.0,1.0}},
  name_{name} {std::cout << "ctor class Shape\n";}

Shape::Shape(Color const& col, std::string const& name):
  color_{col},
  name_{name} {std::cout << "ctor class Shape\n";}

Shape::~Shape(){
  std::cout << "dtor class Shape\n";
}

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