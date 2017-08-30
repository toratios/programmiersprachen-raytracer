#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "shape.hpp"
#include "hit.hpp"

class Triangle : public Shape
{
public:

	Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, 
				std::shared_ptr<Material> const& mat, std::string const& name);

	glm::vec3 const& get_a() const;

	glm::vec3 const& get_b() const;

	glm::vec3 const& get_c() const;


	void check_orientation();

	Hit intersect(Ray const& inray) override;

private:

	glm::vec3 a_;

	glm::vec3 b_;

	glm::vec3 c_;
};

#endif