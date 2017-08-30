#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/detail/func_matrix.hpp>

struct Ray{
  glm::vec3 origin;
  glm::vec3 direction;

  Ray():
  origin{glm::vec3{0.0}},
  direction{glm::vec3{1.0}} {}

  Ray(glm::vec3 ori, glm::vec3 dir):
  origin{ori},
  direction(dir) {}

  friend Ray transformRay(glm::mat4x4 const& transformation_inv, Ray const& ray)
	{	
		Ray new_ray;
		glm::vec3 new_origin(transformation_inv * glm::vec4(ray.origin, 1));
    glm::vec3 new_direction(transformation_inv * glm::vec4(ray.direction, 0));

    new_ray.origin = new_origin;
    new_ray.direction = new_direction;
		return new_ray;
  } 
};

#endif