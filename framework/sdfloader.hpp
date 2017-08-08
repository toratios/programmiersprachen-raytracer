#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "material.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "scene.hpp"
#include "composite.hpp"

struct SDFloader{

  public:
	  SDFloader();

	  static Scene sdfLoad(std::string const& inputFile);
};

#endif
