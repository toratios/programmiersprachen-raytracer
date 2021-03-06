#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "shape.hpp"
#include "hit.hpp"

class Sphere: public Shape{
    glm::vec3 center_;
    float r_;

  public:
    Sphere();
    Sphere(glm::vec3 const& center, float r);
    Sphere(glm::vec3 const& center, float r, std::shared_ptr<Material> const& mat, std::string const& name);
    ~Sphere();

    glm::vec3 const& get_center() const;
    float get_r() const;


    Hit intersect(Ray const& inray) override;
};

#endif