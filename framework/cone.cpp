#include <cone.hpp>
#include <cmath>

Cone::Cone(glm::vec3 const& center, float angle,float height,
			std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	center_{center},
	axis_{glm::vec3{0.0f, -1.0f, 0.0f}},
	angle_{angle},
	height_{height}
	{
		angle_ = angle_ * M_PI / 180;

		axis_ = glm::normalize(axis_);
	}

Hit Cone::intersect(Ray const& inray)
{
	Hit cone_hit;

  Ray ray
  {
    inray.origin,

    glm::normalize(inray.direction)
  };

  float cos2 = cos(angle_) * cos(angle_);

  glm::vec3 co = ray.origin - center_;

  float dv = glm::dot(ray.direction, axis_);

  float cov = glm::dot(co, axis_);

  float A = (dv * dv) - cos2;

  float B = 2 * ((dv * cov) - glm::dot(ray.direction, co) * cos2);

  float C = (cov * cov) - glm::dot(co, co) * cos2;


  float delta = B * B - 4 * A * C;

  float t1 = INFINITY;

  float t2 = INFINITY;

  if(delta < 0)
  {
  	return cone_hit;
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
  	return cone_hit;
  }

  glm::vec3 temp_intersection = ray.origin + ray.direction * t_min;

  glm::vec3 p_c = temp_intersection - center_;

  if(glm::dot(p_c, axis_) < 0)
  {
  	return cone_hit;
  }

  glm::vec3 bottom = center_ + (axis_ * height_);

  if(temp_intersection.y < bottom.y)
  {
  	return cone_hit;
  }

  cone_hit.shape_ = this;
  cone_hit.hit_ = true;
  cone_hit.t_ = t_min;
  cone_hit.intersection_ = ray.origin + ray.direction * cone_hit.t_;

  glm::vec3 ch = -glm::normalize(center_ - cone_hit.intersection_);

  glm::vec3 tangent_vector = -glm::normalize(glm::cross(ray.direction, ch));

  cone_hit.normal_ = glm::normalize(glm::cross(tangent_vector, ch));

  return cone_hit;
}