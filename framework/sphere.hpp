#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "shape.hpp"

class Sphere: public Shape{
    glm::vec3 center_;
    float r_;

  public:
    Sphere();
    Sphere(glm::vec3 const& center, float r);
    Sphere(glm::vec3 const& center, float r, Color const& col, std::string const& name);

    glm::vec3 const& get_center() const;
    float get_r() const;

    std::ostream& print(std::ostream& os) const override;
    float area() const override;
    float volume() const override;
    bool intersect(Ray r, float distance);
};

#endif