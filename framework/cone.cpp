#include <cone.hpp>

Cone::Cone(glm::vec3 const& center, float r, float height,
			std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	center_{center},
	r_{r},
	height_{height}
	{}


glm::vec3 const& Cone::get_center() const
{
	return center_;
}

float Cone::get_radius() const
{
	return r_;
}

float Cone::get_height() const
{
	return height_;
}


Hit Cone::intersect(Ray const& inray)
{

}