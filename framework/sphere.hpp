#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere: public Shape{
    glm::vec3 center_;
    float r_;

  public:
    Sphere();
    Sphere(glm::vec3 const& center, float r);

    glm::vec3 const& get_center() const;
    float get_r() const;

    float area() const override;
    float volume() const override;
};

#endif