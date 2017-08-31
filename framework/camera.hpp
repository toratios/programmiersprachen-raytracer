#ifndef CAMERA_HPP
#define CAMERA_HPP
#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <string>
#include <cmath>
#include <vector>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ray.hpp"


class Camera
{
	
public:

    Camera();

    Camera(std::string name, float fov_x);

    Camera(std::string name, float fov_x, glm::vec3 const& eye,
    		glm::vec3 const& dir, glm::vec3 const& up);


    std::string get_name() const;

    float get_fov() const;

    glm::vec3 const& get_eye() const;

    glm::vec3 const& get_dir() const;

    glm::vec3 const& get_up() const;

    void set_eye(glm::vec3 const& eye);

    Ray generate_ray(float pos_x, float pos_y, float distance) const;

    glm::mat4x4 get_transformation() const;
    glm::mat4x4 get_transformation_inv() const;

    void translate(glm::vec3 const& translate_vec);
    void rotate(float angle, glm::vec3 rotate_vec);

private:

    std::string name_;	//Name

    float fov_x_;		//Horizontaler Öffnungswinkel

    glm::vec3 eye_;     //Position

    glm::vec3 dir_;     //Blickrichtung

    glm::vec3 up_;		//Up-Vector

    glm::mat4x4 transformation_;
    glm::mat4x4 transformation_inv_;

};

#endif
