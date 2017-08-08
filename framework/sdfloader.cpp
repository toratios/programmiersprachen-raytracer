#include "sdfloader.hpp"


Scene SDFloader::sdfLoad(std::string const& inputFile)
{
	Scene scene;

	std::fstream inputfile;
	inputfile.open("material.txt");

	if(inputfile.is_open())
	{
		std::string line;
		std::string word;
		
		while(std::getline(inputfile, line))
		{	
			std::stringstream stream;

			stream << line; 
			stream >> word;

			if(word == "define")
			{
				stream >> word;

				if(word == "material")
				{	
					std::string matname;
					Color ka;
					Color kd;
					Color ks;
					float m;

					stream >> matname;

					stream >> ka.r;
					stream >> ka.g;
					stream >> ka.b;

					stream >> kd.r;
					stream >> kd.g;
					stream >> kd.b;

					stream >> ks.r;
					stream >> ks.g;
					stream >> ks.b;

					stream >> m;


					std::shared_ptr<Material> material = std::make_shared<Material>(matname, ka, kd, ks, m);
					scene.materials_.insert(std::pair<std::string, std::shared_ptr<Material>>(matname, material));
				}

				else if(word == "shape")
				{
					stream >> word;

					if(word == "box")
					{
						std::string boxname;
						glm::vec3 min;
						glm::vec3 max;
						std::string matname;

						stream >> boxname;

						stream >> min.x;
						stream >> min.y;
						stream >> min.z;

						stream >> max.x;
						stream >> max.y;
						stream >> max.z;

						stream >> matname;

						std::shared_ptr<Material> material = (scene.materials_.find(matname)->second);
						std::shared_ptr<Shape> box = std::make_shared<Box>(min, max , material, boxname);
					}

					else if (word == "sphere")
					{
						std::string spherename;
						glm::vec3 center;
						float r;
						std::string matname;

						stream >> spherename;

						stream >> center.x;
						stream >> center.y;
						stream >> center.z;

						stream >> r;

						stream >> matname;

						std::shared_ptr<Material> material = (scene.materials_.find(matname)->second);
						std::shared_ptr<Shape> sphere = std::make_shared<Sphere>(center, r, material, spherename);
					}
				}
			}
		}
	}
	else
	{
		std::cout << "File not found." << std::endl;
	}
}

