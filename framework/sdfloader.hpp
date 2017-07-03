#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "material.hpp"

struct SDFloader{
    std::vector<Material> vecMaterial_;

  public:
	  SDFloader();

	  void sdfLoad(std::string const& inputFile);
};

#endif