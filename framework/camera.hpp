#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <string>


struct Camera
{

    Camera();

    Camera(std::string name, float fov_x);

    Camera(std::string name, float fov_x, glm::vec3 const& eye,
    		glm::vec3 const& dir, glm::vec3 const& up);

    std::string name_;	//Name

    float fov_x_;		//Horizontaler Öffnungswinkel

    glm::vec3 eye_;     //Position

    glm::vec3 dir_;     //Blickrichtung

    glm::vec3 up_;		//Up-Vector

};

#endif