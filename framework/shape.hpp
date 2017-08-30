#ifndef SHAPE_HPP
#define SHAPE_HPP
#define GLM_FORCE_RADIANS
#include <memory>
#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include "glm/vec3.hpp"
#include "glm/glm.hpp"

class Hit;

class Shape{


public:

    Shape();
    Shape(std::string const& name);
    Shape(std::shared_ptr<Material> const& mat, std::string const& name);
    virtual ~Shape();

    std::shared_ptr<Material> const& get_material() const;
    std::string const& get_name() const;

    virtual Hit intersect(Ray const& inray) = 0;


private:

    std::shared_ptr<Material> mat_;
    std::string name_;


};


#endif