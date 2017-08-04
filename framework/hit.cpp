#include "hit.hpp"
#include <cmath>


Hit::Hit():
  hit_ {false},
  t_ {INFINITY},
  intersection_{glm::vec3{INFINITY}},
  normal_{glm::vec3{INFINITY}},
  shape_{nullptr} {}

Hit::Hit(bool hit, float t, glm::vec3 const& intersect, 
      glm::vec3 const& normal, std::shared_ptr<Shape> shape):
  hit_{hit},
  t_{t},
  intersection_{intersect},
  normal_{normal},
  shape_{shape} {}

Hit::Hit(Hit const& hit_copy):
  hit_{hit_copy.hit_},
  t_{hit_copy.t_},
  intersection_{hit_copy.intersection_},
  normal_{hit_copy.normal_},
  shape_{hit_copy.shape_} {}