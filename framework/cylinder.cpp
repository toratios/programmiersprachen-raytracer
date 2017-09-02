#include "cylinder.hpp"
#include <vector>
#include <utility>
#include <cmath>

Cylinder::Cylinder(glm::vec3 const& center, float r, float height,
					std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	center_{center},
	up_vector_{glm::vec3{0.0f, 1.0f, 0.0f}},
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
  Hit cylinder_hit;

  Ray ray
  {
    inray.origin,

    glm::normalize(inray.direction)

  };

	float top_t = INFINITY;

	float bottom_t = INFINITY;

	float front_t = INFINITY;

	float back_t = INFINITY;

	//Top-Intersection


	//Bottom-Intersection


	//Front-Intersection


	//Back-Intersection
}