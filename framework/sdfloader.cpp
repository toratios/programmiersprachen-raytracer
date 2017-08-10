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

		std::map<std::string, std::shared_ptr<Shape>> tempshapesmap;

  	std::vector<std::shared_ptr<Composite>> composites;
  	scene.shapes_ = composites;
		
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
						tempshapesmap.insert(std::pair<std::string, std::shared_ptr<Shape>>(boxname, box));
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
						tempshapesmap.insert(std::pair<std::string, std::shared_ptr<Shape>>(spherename, sphere));
					}

					else if (word == "composite")
					{
						std::string compname;
						std::string shapename;

						stream >> compname;

						std::vector<std::shared_ptr<Shape>> shapes;
						
						while(!stream.eof())
						{
							stream >> shapename;
							auto shape_ptr = tempshapesmap.find(shapename);

							if(shape_ptr != tempshapesmap.end())
							{
								shapes.push_back(shape_ptr->second);
							}
						}
						std::shared_ptr<Composite> comp = std::make_shared<Composite>(compname, shapes);

  					scene.shapes_.push_back(comp);
					}

					else if (word == "light")
					{
						std::string lightname;
						Color color;
						glm::vec3 pos;

						stream >> lightname;


						if(lightname == "ambient")
						{
							stream >> color.r;
							stream >> color.g;
							stream >> color.b;

							scene.ambient_ = color;
						}
						else
						{
							stream >> pos.x;
							stream >> pos.y;
							stream >> pos.z;

							stream >> color.r;
							stream >> color.g;
							stream >> color.b;
						
							std::shared_ptr<Light> light = std::make_shared<Light>(lightname, pos, color);
							scene.lights_.push_back(light);
						}
					}

					else if (word == "camera")
					{
						std::string cameraname;
						float fov;
						glm::vec3 eye;
						glm::vec3 dir;
						glm::vec3 up;

						stream >> cameraname;

						stream >> fov;

						stream >> eye.x;
						stream >> eye.y;
						stream >> eye.z;

						stream >> dir.x;
						stream >> dir.y;
						stream >> dir.z;

						stream >> up.x;
						stream >> up.y;
						stream >> up.z;

						scene.camera_ = Camera{cameraname, fov, eye, dir, up};
					}
				}
			}
		}
	}

	else
	{
		std::cout << "File not found." << std::endl;
	}

	return scene;
}

