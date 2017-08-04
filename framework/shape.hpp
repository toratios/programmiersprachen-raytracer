#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include "material.hpp"
#include "ray.hpp"

class Shape{
    std::shared_ptr<Material> mat_;
    std::string name_;

  public:
    Shape();
    Shape(std::string const& name);
    Shape(std::shared_ptr<Material> const& mat, std::string const& name);
    virtual ~Shape();

    std::shared_ptr<Material> const& get_material() const;
    std::string const& get_name() const;

    virtual std::ostream& print(std::ostream& os) const;
    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual bool intersect(Ray const& ray, float& t) = 0;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif