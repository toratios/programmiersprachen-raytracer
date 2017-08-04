#include "hit.hpp"
#include <cmath>


Hit::Hit():
  hit_ {false},
  t_ {INFINITY},
  intersection_{glm::vec3{INFINITY}},
  normal_{glm::vec3},
  shape_{nullptr} {}

Hit::Hit(bool hit, float t, glm::vec3 const& intersect, 
      glm::vec3 const& normal, std::shared_ptr<Shape> shape):
  hit_{hit},
  t_{t},
  intersection_{intersect},
  normal_{normal},
  shape_{shape} {}