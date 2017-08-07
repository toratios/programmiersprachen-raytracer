#include "composite.hpp"

	Composite::Composite():
		name_{"default_composite"},
		shapes_{}
		{}

	Composite::Composite(std::string name):
		name_{name},
		shapes_{}
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
		Hit hit;
		Hit temp_hit;

		for(auto& shape : shapes_)
		{
			temp_hit = shape -> intersect(ray);

			if(temp_hit.t_ < hit.t_)
			{
				hit = temp_hit;
			}
		}

		return hit;
	}
