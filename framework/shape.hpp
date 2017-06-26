#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include "ray.hpp"

//typedef std::string String;
//typdef glm::vec3 Vec3

class Shape{
    Color color_;
    std::string name_;

  public:
    Shape();
    Shape(std::string const& name);
    Shape(Color const& col, std::string const& name);
    virtual ~Shape();

    Color const& get_color() const;
    std::string const& get_name() const;

    virtual std::ostream& print(std::ostream& os) const;
    virtual float area() const = 0;
    virtual float volume() const = 0;
    virtual bool intersect(Ray const& ray, float& t) = 0;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif