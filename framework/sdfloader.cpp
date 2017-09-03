#include "sdfloader.hpp"



Scene SDFloader::sdfLoad(std::string const& inputFile)
{
	Scene scene;

	std::fstream inputfile;
	inputfile.open(inputFile);

	if(inputfile.is_open())
	{
		std::string line;
		std::string word;

		std::map<std::string, std::shared_ptr<Shape>> tempshapesmap;
		std::map<std::string, std::shared_ptr<Composite>> tempcompmap;

  	std::vector<std::shared_ptr<Composite>> composites;
		
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
					float opac;
					float refract;

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
					stream >> opac;
					stream >> refract;


					std::shared_ptr<Material> material = std::make_shared<Material>(matname, ka, kd, ks, m, opac, refract);
					scene.materials_.insert(std::pair<std::string, std::shared_ptr<Material>>(matname, material));
					std::cout << "\nmaterial added to scene " << matname;
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
						std::cout << "\nbox added to temshapepmap " << boxname;
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
						std::cout << "\nsphere added to tempshapemap " << spherename;
					}

					else if (word == "cone")
					{
						std::string conename;
						glm::vec3 center;
						float angle;
						float height;
						std::string matname;

						stream >> conename;

						stream >> center.x;
						stream >> center.y;
						stream >> center.z;

						stream >> angle;
						stream >> height;

						stream >> matname;

						std::shared_ptr<Material> material = (scene.materials_.find(matname)->second);
						std::shared_ptr<Shape> cone = std::make_shared<Cone>(center, angle, height, material, conename);
						tempshapesmap.insert(std::pair<std::string, std::shared_ptr<Shape>>(conename, cone));
					}

					else if (word == "cylinder")
					{
						std::string cylname;
						glm::vec3 center;
						float r;
						float height;
						std::string matname;

						stream >> cylname;

						stream >> center.x;
						stream >> center.y;
						stream >> center.z;

						stream >> r;
						stream >> height;

						stream >> matname;

						std::shared_ptr<Material> material = (scene.materials_.find(matname)->second);
						std::shared_ptr<Shape> cyl = std::make_shared<Cylinder>(center, r, height, material, cylname);
						tempshapesmap.insert(std::pair<std::string, std::shared_ptr<Shape>>(cylname, cyl));
					}

					else if (word == "triangle")
					{
						std::string triname;
						glm::vec3 a;
						glm::vec3 b;
						glm::vec3 c;
						std::string matname;

						stream >> triname;

						stream >> a.x;
						stream >> a.y;
						stream >> a.z;

						stream >> b.x;
						stream >> b.y;
						stream >> b.z;

						stream >> c.x;
						stream >> c.y;
						stream >> c.z;

						stream >> matname;

						std::shared_ptr<Material> material = (scene.materials_.find(matname)->second);
						std::shared_ptr<Shape> tri = std::make_shared<Triangle>(a, b, c, material, triname);
						tempshapesmap.insert(std::pair<std::string, std::shared_ptr<Shape>>(triname, tri));
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
								std::cout << "\nshape added from tempshapemap to tempvector " << shape_ptr->first;
							}

							auto comp_ptr = tempcompmap.find(shapename);

							if(comp_ptr != tempcompmap.end())
							{
								shapes.push_back(comp_ptr->second);
								std::cout << "\ncomp added from tempcompmap to tempvector " << comp_ptr->first;
							}
						}
						std::shared_ptr<Composite> comp = std::make_shared<Composite>(compname, shapes);
						tempcompmap.insert(std::pair<std::string, std::shared_ptr<Composite>>(compname, comp));
						std::cout << "\ncomp added to tempcompmap " << compname;
					}
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
						std::cout << "\nambientlight added to scene: " << lightname;
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
						std::cout << "\nlight added to scene: " << lightname;
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
					std::cout << "\ncamera added to scene: " << cameraname;
				}
			}
		}

		for(auto it = tempcompmap.cbegin(); it != tempcompmap.cend(); ++it)
		{
    	composites.push_back(it->second);
			std::cout << "\ncomp pushed from tempcompmap in compvector: " << it->first;
		}

		scene.shapes_ = composites;
		std::cout << "\ncompvector added to scene";
	}

	else
	{
		std::cout << "File not found." << std::endl;
	}

	return scene;
}