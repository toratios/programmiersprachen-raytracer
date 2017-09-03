#include <cone.hpp>
#include <cmath>
#include <vector>
#include <utility>

Cone::Cone(glm::vec3 const& center, float angle,float height,
			std::shared_ptr<Material> const& mat, std::string const& name):
	Shape{mat, name},
	center_{center},
	axis_{glm::vec3{0.0f, 1.0f, 0.0f}},
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

  Ray ray = transformRay(world_transformation_inv(), inray);

  float Ird = ray.direction.length();

  ray.direction = glm::normalize(ray.direction);

  std::vector<std::pair<float, glm::vec3>> points;
}