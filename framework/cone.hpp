#ifndef CONE_HPP
#define CONE_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "shape.hpp"
#include "hit.hpp"

class Cone : public Shape
{
public:

	Cone(glm::vec3 const& center, float angle, std::shared_ptr<Material> const& mat,
				std::string const& name);

	Hit intersect(Ray const& inray) override;

private:

	glm::vec3 center_;

	glm::vec3 axis_;

	float angle_;
};

#endif