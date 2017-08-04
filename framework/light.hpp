#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include <glm/vec3>
#include "color.hpp"

struct Light
{

	std::string name_;		//Name

	glm::vec3 pos_;			//Position
	
	Color color_;			//Farbe

};

#endif