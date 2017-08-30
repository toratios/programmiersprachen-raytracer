#include "triangle.hpp"

Triangle::Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c, 
					std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	a_{a},
	b_{b},
	c_{c}
	{/*check_orientation();*/}


glm::vec3 const& Triangle::get_a() const
{
	return a_;
}

glm::vec3 const& Triangle::get_b() const
{
	return b_;
}

glm::vec3 const& Triangle::get_c() const
{
	return c_;
}


void Triangle::check_orientation()
{
	glm::vec3 edge_1 = b_ - a_;

	glm::vec3 edge_2 = c_ - a_;

	glm:: vec3 normal = glm::normalize(glm::cross(edge_1, edge_2));

	if(normal.z < 0)
	{
		glm::vec3 temp;

		temp = b_;

		b_ = c_;

		c_ = temp;
	} 
}

Hit Triangle::intersect(Ray const& inray)
{
	Hit triangle_hit;

	Ray ray
	{
		inray.origin,

		glm::normalize(inray.direction)
	};

	glm::vec3 a_b = b_ - a_;

	glm::vec3 a_c = c_ - a_;

	glm::vec3 normal = glm::cross(a_b, a_c);


	float NdotRayDirection = glm::dot(normal, ray.direction);

	if(fabs(NdotRayDirection) == 0)
	{
		return triangle_hit;
	}

	float d = glm::dot(normal, a_);

	float t = (glm::dot(normal, ray.origin) + d) / NdotRayDirection;

	if(t < 0)
	{
		return triangle_hit;
	}

	glm::vec3 p = ray.origin + t * ray.direction;

	glm::vec3 c;


	glm::vec3 edge_0 = b_ - a_;

	glm::vec3 vp0 = p - a_;

	c = glm::cross(edge_0, vp0);

	if(glm::dot(normal, c) < 0)
	{
		return triangle_hit;
	}


	glm::vec3 edge_1 = c_ - b_;

	glm::vec3 vp1 = p - b_;

	c = glm::cross(edge_1, vp1);

	if(glm::dot(normal, c) < 0)
	{
		return triangle_hit;
	}


	glm::vec3 edge_2 = a_ - c_;

	glm::vec3 vp2 = p - c_;

	c = glm::cross(edge_2, vp2);

	if(glm::dot(normal, c) < 0)
	{
		return triangle_hit;
	}


	triangle_hit.t_ = t;
	triangle_hit.hit_ = true;
	triangle_hit.shape_ = this;
	triangle_hit.normal_ = glm::normalize(normal);
	triangle_hit.intersection_ = ray.origin + ray.direction * t;

	return triangle_hit; 
}