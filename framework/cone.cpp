#include <cone.hpp>
#include <cmath>
#include <vector>

Cone::Cone(glm::vec3 const& center, float angle,float height,
			std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	center_{center},
	axis_{glm::vec3{0.0f, -1.0f, 0.0f}},
	angle_{angle},
	height_{height}
	{
		angle_ = angle_ * M_PI / 180;
		r_ = height_ * tan(angle_);
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

  std::vector<float> points;

  float cos2a = cos(angle_) * cos(angle_);
  float sin2a = 1 - cos2a;
  glm::vec3 pa = center_ + axis_ * height_;
  glm::vec3 va = -axis_;
  glm::vec3 deltaP = ray.origin - pa;

  float c1 = glm::dot(ray.direction, va);
  glm::vec3 c2 = va * c1;
  float c3 = glm::dot(deltaP, va);
  glm::vec3 c4 = va * c3;

  float a = cos2a * glm::dot(ray.direction - c2, ray.direction - c2) - sin2a * c1 * c1;
  float b = 2 * cos2a * glm::dot(ray.direction - c2, deltaP - c4) - 2 * sin2a * (c1 * c3);
  float c = cos2a * glm::dot(deltaP - c4, deltaP - c4) - sin2a * (c3 * c3);

  float d = b * b - 4 * a * c;

  if(d < 0)
  {
    return cone_hit;
  }

  else
  {
    d = sqrtf(d);

    float t1 = ((-1 * b) + d) / (2 * a);
    float t2 = ((-1 * b) - d) / (2 * a);

    if(t1 >= 0)
    {
      if(glm::dot(axis_, (ray.origin - center_) + ray.direction * t1) > 0 &&
          glm::dot(axis_, (ray.origin - pa) + ray.direction * t1) < 0)
      {
        points.push_back(t1);
      }

    }

    if(t2 >= 0)
    {
      if(glm::dot(axis_, (ray.origin - center_) + ray.direction * t2) > 0 &&
          glm::dot(axis_, (ray.origin - pa) + ray.direction * t2) < 0)
      {
        points.push_back(t2);
      }

    }
  }

  float denom = glm::dot(ray.direction, axis_);

  if(denom > 0.001f)
  {
    glm::vec3 co = center_ - ray.origin;
    float t3 = glm::dot(co, axis_) / denom;

    if(t3 > 0 && glm::dot(ray.direction * t3 - co, ray.direction * t3 - co) <= r_ * r_)
    {
      points.push_back(t3);
    }
  }

  float minT = INFINITY;
  bool flag = false;

  for(int i = 0; i < points.size(); ++i)
  {
    if(minT > points[i] && points[i] >= 0)
    {
      minT = points[i];
      flag = true;
    }
  }

  if(flag)
  {
    glm::vec3 normal;

    float t = minT;

    cone_hit.hit_ = true;
    cone_hit.shape_ = this;
    cone_hit.t_ = t;
    cone_hit.intersection_ = ray.origin + ray.direction * t;

    glm::vec3 temp_intersection = cone_hit.intersection_;

    if(std::fabs(glm::dot(temp_intersection - center_, axis_)) < 0.01f)
    {
      normal = -axis_;
    }

    else
    {
      glm::vec3 top = center_ + axis_ * height_;
      glm::vec3 perp = glm::cross(-axis_, temp_intersection - top);

      normal = glm::cross(temp_intersection - top, perp);
    }




    cone_hit.normal_ = glm::normalize(normal);


    return cone_hit;
  }  

  return cone_hit;
}