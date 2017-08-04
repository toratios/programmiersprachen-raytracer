/*#include "sdfloader.hpp"


Scene SDFloader::sdfLoad(std::string const& inputFile)
{
	Scene scene;

	std::fstream input;
	input.open("material.txt");

	if(input.is_open())
	{
		std::string line;
		std::string word;
		
		while(std::getline(input, line))
		{	
			stream << line; 
			stream >> word;	
			if(word == "define")
			{
				stream >> word;

				if(word == "material")
				{
					Material mat;
						
					stream >> mat.name_;
					stream >> mat.ka_.r;
					stream >> mat.ka_.g;
					stream >> mat.ka_.b;
					stream >> mat.kd_.r;
					stream >> mat.kd_.g;
					stream >> mat.kd_.b;
					stream >> mat.ks_.r;
					stream >> mat.ks_.g;
					stream >> mat.ks_.b;

					//vecMaterial_.push_back(mat);
				}
			}
		}
	}
	else
	{
		std::cout << "File not found." << std::endl;
	}
}

*/