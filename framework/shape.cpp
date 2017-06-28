#include "shape.hpp"

Shape::Shape():
  mat_{},
  name_{"Shape"} {/*std::cout << "ctor class Shape\n";*/}

Shape::Shape(std::string const& name):
  mat_{},
  name_{name} {/*std::cout << "ctor class Shape\n";*/}

Shape::Shape(Material const& mat, std::string const& name):
  mat_{mat},
  name_{name} {/*std::cout << "ctor class Shape\n";*/}

Shape::~Shape(){
  /*std::cout << "dtor class Shape\n";*/
}

Material const& Shape::get_material() const{
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