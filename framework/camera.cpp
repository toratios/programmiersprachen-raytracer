#include "camera.hpp"

	Camera::Camera():
		name_{"default"},
		fov_x_{0.0f},
		eye_{0.0f,0.0f,0.0f},
		dir_{0.0f,0.0f,-1.0f},
		up_{0.0f,1.0f,0.0f},
		transformation_{glm::mat4(1.0)},
		transformation_inv_{glm::mat4(1.0)},
		rotation_{glm::mat4(1.0)},
		translation_{glm::mat4(1.0)}
		{}


  Camera::Camera(std::string name, float fov_x):
   	name_{name},
   	fov_x_{fov_x},
  	eye_{0.0f,0.0f,0.0f},
		dir_{0.0f,0.0f,-1.0f},
		up_{0.0f,1.0f,0.0f},
		transformation_{glm::mat4(1.0)},
		transformation_inv_{glm::mat4(1.0)},
		rotation_{glm::mat4(1.0)},
		translation_{glm::mat4(1.0)}
		{}

  Camera::Camera(std::string name, float fov_x, glm::vec3 const& eye,
  	glm::vec3 const& dir, glm::vec3 const& up):
   	name_{name},
  	fov_x_{fov_x},
  	eye_{eye},
		dir_{dir},
		up_{up},
		transformation_{glm::mat4(1.0)},
		transformation_inv_{glm::mat4(1.0)},
		rotation_{glm::mat4(1.0)},
		translation_{glm::mat4(1.0)}
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

  void Camera::set_eye(glm::vec3 const& eye)
  {
  	eye_ = eye;
  }

	Ray Camera::generate_ray(float pos_x, float pos_y, float distance) const
	{
		Ray eye_ray;
    eye_ray.origin = glm::vec3(transformation_inv_ * glm::vec4(0, 0, 0, 1));
		eye_ray.direction = glm::vec3(transformation_inv_ * (glm::vec4(pos_x, pos_y, -distance, 0)));
		//std::cout << glm::to_string(eye_ray.origin) << "\n"; 
		//std::cout << glm::to_string(eye_ray.direction) << "\n"; 
		return eye_ray;
	}

	glm::mat4x4 Camera::get_transformation() const
	{
		return transformation_;
	}

	glm::mat4x4 Camera::get_transformation_inv() const
	{
		return transformation_inv_;
	}

	void Camera::translate(glm::vec3 const& translate_vec)
	{
		glm::mat4 T;
    T[0] = glm::vec4{1.0f, 0.0f, 0.0f, 0.0f};
    T[1] = glm::vec4{0.0f, 1.0f, 0.0f, 0.0f};
    T[2] = glm::vec4{0.0f, 0.0f, 1.0f, 0.0f};
		T[3] = glm::vec4{translate_vec.x, translate_vec.y, translate_vec.z, 1.0f};
		translation_ = T;
    transformation_ = translation_ * rotation_;
		transformation_inv_ = glm::inverse(transformation_);
	}

	void Camera::rotate(float angle, glm::vec3 const& rotate_vec)
	{
		float angle_rad = (angle*3.1415926535897f)/180.0f;
		glm::mat4x4 R = glm::rotate(glm::mat4(1.0), angle_rad, rotate_vec);
		rotation_ = R;
		transformation_ = translation_ * rotation_;
		transformation_inv_ = glm::inverse(transformation_);
	}