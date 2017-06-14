#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"

//typedef std::string String;
//typdef glm::vec3 Vec3

class Shape{
    Color color_;
    std::string name_;

  public:
    Shape();
    Shape(std::string const& name);
    Shape(Color const& col, std::string const& name);

    Color const& get_color() const;
    std::string const& get_name() const;

    virtual float area() const = 0;
    virtual float volume() const = 0;
};

#endif