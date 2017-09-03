#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "shape.hpp"
#include "hit.hpp"

class Cylinder : public Shape
{
public:

	Cylinder(glm::vec3 const& center, float r, float height,
				std::shared_ptr<Material> const& mat, std::string const& name);

	glm::vec3 const& get_center() const;

	float get_radius() const;

	float get_height() const;

	Hit intersect(Ray const& inray) override;

private:

	glm::vec3 center_;

	glm::vec3 axis_;

	float r_;

	float height_;
};

#endif