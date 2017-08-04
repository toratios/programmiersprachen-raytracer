#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3>
#include <glm/mat4>


struct Camera
{

    glm::vec3 pos_;     //Position

    glm::vec3 dir_;     //Direction

    glm::mat4 c_;       //Transformation

};

#endif