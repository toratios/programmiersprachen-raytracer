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
for (int i = 1; i <= 180; i += 1){

    Scene test_scene;

    SDFloader loader{};

    std::string file = "./sdf_"+std::to_string(i);
    test_scene = loader.sdfLoad(file);

//=================Renderer==============================================================

    unsigned const width = 1920;
    unsigned const height = 1080;

    std::string const filename = "./frame"+std::to_string(i)+".ppm";

    Renderer test_renderer{width, height, filename, test_scene};

    std::thread thr([&test_renderer]() { test_renderer.render_scene(); });

    std::cout  << "frame" << i <<"/5\n"; 

    thr.join();
  }

  return 0;
}