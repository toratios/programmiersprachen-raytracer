#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "shape.hpp"
#include "hit.hpp"

class Box: public Shape
{
public:

  Box();

  Box(glm::vec3 const& min, glm::vec3 const& max);

  Box(glm::vec3 const& min, glm::vec3 const& max, std::shared_ptr<Material> const& mat, std::string const& name);

  glm::vec3 const& get_min() const;
  
  glm::vec3 const& get_max() const;

  void sortMinMax();

  Hit intersect(Ray const& inray) override;

private:

	glm::vec3 min_; 

  glm::vec3 max_;
};

#endif