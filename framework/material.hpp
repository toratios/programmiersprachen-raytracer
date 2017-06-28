#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"

struct material{
  std::string name;
  Color ka;
  Color kd;
  Color ks;
  float m;
};

#endif