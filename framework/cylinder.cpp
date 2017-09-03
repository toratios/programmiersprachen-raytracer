#include "cylinder.hpp"
#include <vector>
#include <utility>
#include <cmath>
#include <vector>
#include <utility>
#include <glm/gtx/intersect.hpp>
#include <iostream>

Cylinder::Cylinder(glm::vec3 const& center, float r, float height,
					std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	center_{center},
	axis_{glm::vec3{0.0f, 1.0f, 0.0f}},
	r_{r},
	height_{height}
	{
		axis_ = glm::normalize(axis_);
	}


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

  Ray ray = transformRay(world_transformation_inv(), inray);

  float Ird = ray.direction.length();

  ray.direction = glm::normalize(ray.direction);

  std::vector<std::pair<float, glm::vec3>> points;

  glm::vec3 alpha = axis_ * glm::dot(ray.direction, axis_);
  glm::vec3 deltaP = ray.origin - center_;
  glm::vec3 beta = axis_ * glm::dot(deltaP, axis_);
  glm::vec3 center2 = center_ + axis_ * height_;

  float a = glm::dot(ray.direction - alpha, ray.direction - alpha);
  float b = 2 * glm::dot(ray.direction - alpha, deltaP - beta);
  float c = glm::dot(deltaP - beta, deltaP - beta) - r_ * r_;

  float d = b * b - 4 * a * c;

  if(d < 0)
  {
  	return cylinder_hit;
  }

  else
  {
  	d = sqrtf(d);

  	float t1 = ((-1 * b) + d) / (2 * a);
  	float t2 = ((-1 * b) - d) / (2 * a);

  	if(t1 >= 0)
  	{
  		if(glm::dot(axis_, (ray.origin - center_) + ray.direction * t1) > 0 &&
  				glm::dot(axis_, (ray.origin - center2) + ray.direction * t1) < 0)
  		{
  			glm::vec3 temp_intersection = ray.origin + ray.direction * t1;

  			glm::vec3 temp_center
  			{
  				center_.x,
  				temp_intersection.y,
  				center_.z
  			};

  			glm::vec3 temp_normal = temp_intersection - temp_center;

  			points.push_back(std::make_pair(t1, temp_normal));
  		}
  	}

  	if(t2 >= 0)
  	{
  		if(glm::dot(axis_, (ray.origin - center_) + ray.direction * t2) > 0 &&
  				glm::dot(axis_, (ray.origin - center2) + ray.direction * t2) < 0)
  		{
  			glm::vec3 temp_intersection = ray.origin + ray.direction * t2;

  			glm::vec3 temp_center
  			{
  				center_.x,
  				temp_intersection.y,
  				center_.z
  			};

  			glm::vec3 temp_normal = temp_intersection - temp_center;

  			points.push_back(std::make_pair(t2, temp_normal));
  		}
  	}
  }

  float denom = glm::dot(ray.direction, axis_);

  if(denom > 0.001)
  {
  	glm::vec3 co = center_ - ray.origin;
  	float t3 = glm::dot(co, axis_) / denom;

  	if(t3 > 0 && glm::dot((ray.direction * t3 - co), (ray.direction * t3 - co)) <= r_ * r_)
  	{
  		points.push_back(std::make_pair(t3, -axis_));
  	}
  }

  else if( denom < 0.001)
  {
  	glm::vec3 co2 = center2 - ray.origin;
  	float t4 = glm::dot(co2, axis_) / denom;

  	if(t4 > 0 && glm::dot((ray.direction * t4 - co2), (ray.direction * t4 - co2)) <= r_ * r_)
  	{
  		points.push_back(std::make_pair(t4, axis_));
  	}
  }

  float minT = INFINITY;
  bool flag = false;
  glm::vec3 normal;

  for(int i = 0; i < points.size(); ++i)
  {
  	if(minT > points[i].first && points[i].first >= 0)
  	{
  		minT = points[i].first;
  		normal = points[i].second;
  		flag = true;
  	}
  }

	if(flag)
	{
		float t = minT / Ird;

		cylinder_hit.hit_ = true;
		cylinder_hit.shape_ = this;
		cylinder_hit.t_ = t;
		cylinder_hit.intersection_ = ray.origin + ray.direction * t;
		cylinder_hit.normal_ = glm::normalize(normal);

		return cylinder_hit;
	}  

	return cylinder_hit;
}


