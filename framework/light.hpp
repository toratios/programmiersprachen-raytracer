#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"

struct Light
{

	Light():
		name_{"default_light"},
		pos_{0.0},
		color_{1.0,1.0,1.0},
		brightness_{1.0f} 
		{
			color_ *= brightness_;
		}

		Light(std::string const& name, glm::vec3 const& pos, Color const& col):
		name_{name},
		pos_{pos},
		color_{col},
		brightness_{1.0f}
		{
			color_ *= brightness_;
		}

	Light(std::string const& name, glm::vec3 const& pos, Color const& col, float brightness):
		name_{name},
		pos_{pos},
		color_{col},
		brightness_{brightness}
		{
			color_ *= brightness_;
		}


	std::string name_;		//Name

	glm::vec3 pos_;			//Position

	Color color_;			//Color

	float brightness_;
};

#endif