#include "cylinder.hpp"
#include <vector>
#include <utility>
#include <cmath>

Cylinder::Cylinder(glm::vec3 const& center, float r, float height,
					std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	center_{center},
	axis_{glm::vec3{0.0f, 1.0f, 0.0f}},
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

  glm::vec3 v = ray.direction;

  glm::vec3 va = axis_;

  glm::vec3 pa = center_;

  glm::vec3 delta_p = ray.origin - pa;

  glm::vec3 a = (v - glm::dot(v, va) * va);

  glm::vec3 c = delta_p - glm::dot(delta_p, va) * va;

  float A = glm::dot(a, a);

  float B = 2 * glm::dot(a, (delta_p - (glm::dot(delta_p, va)) * va));

  float C = glm::dot(c, c) - r_ * r_;


  float delta = B * B - 4 * A * C;

  float t1 = INFINITY;

  float t2 = INFINITY;

  if(delta < 0)
  {
  	return cylinder_hit;
  }

  else if(delta == 0)
  {
  	t1 = (-B) / (2 * A);
  }

  else if(delta > 0)
  {
  	t1 = ((-B) - sqrtf(delta)) / (2 * A);

  	t2 = ((-B) + sqrtf(delta)) / (2 * A);
  }

  float t_min = std::min(t1, t2);

  if(t_min < 0)
  {
  	return cylinder_hit;
  }

   glm::vec3 temp_intersection = ray.origin + ray.direction * t_min;

   glm::vec3 top = center_ + (axis_ * height_);

  if(temp_intersection.y < center_.y)
  {
  	return cylinder_hit;
  }

  if(temp_intersection.y > top.y)
  {
  	//return cylinder_hit;
  }


  cylinder_hit.shape_ = this;
  cylinder_hit.hit_ = true;
  cylinder_hit.t_ = t_min;
  cylinder_hit.intersection_ = ray.origin + ray.direction * cylinder_hit.t_;

  glm::vec3 temp_center{center_.x,
  											cylinder_hit.intersection_.y,
  											center_.z};

 	glm::vec3 normal = glm::normalize(cylinder_hit.intersection_ - temp_center);

 	cylinder_hit.normal_ = normal;

  return cylinder_hit;
}