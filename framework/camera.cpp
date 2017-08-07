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

	std::string Camera::get_name() const
	{
		return name_;
	}

    float Camera::get_fov() const
    {
    	return fov_x_;
    }

    glm::vec3 const& Camera::get_eye() const
    {
    	return eye_;
    }

    glm::vec3 const& Camera::get_dir() const
    {
    	return dir_;
    }

    glm::vec3 const& Camera::get_up() const
    {
    	return up_;
    }

	std::vector<Ray> Camera::generate_rays(unsigned int width, unsigned int height) const
	{
		std::vector<Ray> eye_rays;

		float distance = (width / 2) / tan(fov_x_ * M_PI / 360);

		for(int x = ((int)width / -2); x < ((int)width / 2); ++x)
		{
			for(int y = ((int)height / -2); y < ((int)height / 2); ++y)
			{
				glm::vec3 temp_direction(x, y, -(distance));

				Ray temp_ray(eye_, temp_direction);

				eye_rays.push_back(temp_ray);
			}
		}

		return eye_rays;
	}