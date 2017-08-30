#include "cylinder.hpp"

Cylinder::Cylinder(glm::vec3 const& center, float r, float height,
					std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	center_{center},
	r_{r},
	height_{height}
	{}


glm::vec3 const& Cylinder::get_center() const
{
	return center_;
}

float Cylinder::get_radius() const
{
	return r_;
}

float Cylinder::get_height() const
{
	return height_;
}


Hit Cylinder::intersect(Ray const& inray)
{
	
}