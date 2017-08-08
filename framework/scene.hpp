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
#include "color.hpp"
#include "composite.hpp"

struct Scene
{
	Scene():
		ambient_{},
		camera_{}
		{}

	Scene(Color const& ambient, Camera const& camera):
		ambient_{ambient},
		camera_{camera}
		{}


    //Shapes
    std::vector<std::shared_ptr<Composite>> shapes_;

    //Materials
    std::map<std::string, std::shared_ptr<Material>> materials_;

    //Lights
    std::vector<std::shared_ptr<Light>> lights_;

    //Ambient Light
    Color ambient_;

    //Camera
    Camera camera_;

};

#endif