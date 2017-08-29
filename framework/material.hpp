#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include <ostream>

struct Material{
  std::string name_;
  Color ka_;
  Color kd_;
  Color ks_;
  float m_;
  float reflect_;
  float opac_;
  float refract_;

  Material():
  name_{"default material"},
  ka_{Color{0.1,0.1,0.1}},
  kd_{Color{0.2,0.2,0.2}},
  ks_{Color{0.3,0.3,0.3}},
  m_{0.0},
  reflect_{0.0f},
  opac_{1.0},
  refract_{1.0}
  {}

  Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m):
  name_{name},
  ka_{ka},
  kd_{kd},
  ks_{ks},
  m_{m},
  reflect_{0.0f},
  opac_{1.0},
  refract_{1.0}
  {}

  Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m, float reflect):
  name_{name},
  ka_{ka},
  kd_{kd},
  ks_{ks},
  m_{m},
  reflect_{reflect},
  opac_{1.0},
  refract_{1.0}
  {}

  Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks, float m, float reflect, float opac, float refract):
  name_{name},
  ka_{ka},
  kd_{kd},
  ks_{ks},
  m_{m},
  reflect_{reflect},
  opac_{opac},
  refract_{refract}
  {}

  friend std::ostream& operator<<(std::ostream& os, Material const& mat) {
    os << "Name: " << mat.name_ << "\n" 
    << "Color ka: " << mat.ka_ 
    << "Color kd: " << mat.ks_ 
    << "Color ks: " << mat.ks_
    << "m: " << mat.m_ << "\n";
    return os; 
  }

};

#endif