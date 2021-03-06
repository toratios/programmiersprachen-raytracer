#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "box.hpp"
#include "sphere.hpp"
#include "cone.hpp"
#include "cylinder.hpp"
#include "triangle.hpp"
#include "scene.hpp"

struct SDFloader{

  public:
	  //SDFloader();

	  static Scene sdfLoad(std::string const& inputFile);
};

#endif
