#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <map>
#include <string>
#include "shape.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "light.hpp"

struct Scene
{
    using namespace std;

    //Shapes
    vector<shared_ptr<Shape>> shapes_;

    //Materials
    map<string, shared_ptr<Material>> materials_;

    //Camera
    Camera camera;

    //Lights
    vector<shared_ptr<Light>> lights_;


};

#endif