#include "composite.hpp"

	Composite::Composite():
		name_{"default_composite"},
		shapes_{}
		{}

	Composite::Composite(std::string name):
		name_{name},
		shapes_{}
		{}

	Composite::Composite(std::string name, std::vector<std::shared_ptr<Shape>> shapes):
		name_{name},
		shapes_{shapes}
		{}

	void Composite::add(std::shared_ptr<Shape> const& shape)
	{
		shapes_.push_back(shape);
	}

	std::vector<std::shared_ptr<Shape>> Composite::get_children() const
	{
		return shapes_;
	}

	Hit Composite::intersect(Ray const& ray)
	{
		Hit closest_hit;
		Hit temp_hit;

		for(auto& shape : shapes_)
		{
			temp_hit = shape -> intersect(ray);

			if(temp_hit.t_ < closest_hit.t_)
			{
				closest_hit = temp_hit;
			}
		}

		return closest_hit;
	}
