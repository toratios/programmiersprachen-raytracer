#include "camera.hpp"

	Camera::Camera():
		name_{"default"},
		fov_x_{0.0f},
		eye_{0.0f,0.0f,0.0f},
		dir_{0.0f,0.0f,-1.0f},
		up_{0.0f,1.0f,0.0f}
		{}


   	Camera::Camera(std::string name, float fov_x):
   		name_{name},
   		fov_x_{fov_x},
   		eye_{0.0f,0.0f,0.0f},
		dir_{0.0f,0.0f,-1.0f},
		up_{0.0f,1.0f,0.0f}
		{}

    Camera::Camera(std::string name, float fov_x, glm::vec3 const& eye,
    				glm::vec3 const& dir, glm::vec3 const& up):
       	name_{name},
   		fov_x_{fov_x},
   		eye_{eye},
		dir_{dir},
		up_{up}
		{}