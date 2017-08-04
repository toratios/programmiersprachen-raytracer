#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>


struct Camera
{

    Camera();

    //rotate();


    glm::vec3 pos_;     //Position

    glm::vec3 dir_;     //Direction

    glm::mat4 c_;       //Transformation

};

#endif