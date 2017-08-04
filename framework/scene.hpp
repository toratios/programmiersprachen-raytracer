#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include <map>
#include <string>
#include "shape.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "light.hpp"

struct Scene
{

    //Shapes
    std::vector<std::shared_ptr<Shape>> shapes_;

    //Materials
    std::map<std::string, std::shared_ptr<Material>> materials_;

    //Camera
    Camera camera_;

    //Lights
    std::vector<std::shared_ptr<Light>> lights_;
};

#endif