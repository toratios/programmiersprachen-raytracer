#include <renderer.hpp>
#include <window.hpp>
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <scene.hpp>
#include <hit.cpp>
#include <color.hpp>
#include <renderer.hpp>
#include <box.cpp>
#include <sphere.cpp>
#include <shape.cpp>
#include <composite.hpp>
#include <camera.hpp>
#include <light.hpp>
#include <material.hpp>
#include <pixel.hpp>
#include <ray.hpp>
#include <ppmwriter.hpp>
#include <vector>
#include <memory>
#include <map>
#include <glm/glm.hpp>
#include <string>

#include <sdfloader.cpp>

int main(int argc, char* argv[])
{
  Scene test_scene;

  SDFloader loader{};

  std::string file = "./sdf_test";
  test_scene = loader.sdfLoad(file);

//=================Renderer==============================================================

  unsigned const width = 800;
  unsigned const height = 600;

  std::string const filename = "./test_sdf2.ppm";

  Renderer test_renderer{width, height, filename, test_scene};

  std::thread thr([&test_renderer]() { test_renderer.render_scene(); });

  thr.join();

  return 0;
}