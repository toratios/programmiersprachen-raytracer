#include "camera.hpp"

Camera::Camera():
	pos_{glm::vec3{0.0}},
	dir_{glm::vec3{0.0, 0.0, -1.0}},
	c_{glm::mat4{0.0}}
	{}