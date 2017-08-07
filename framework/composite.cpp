#include "composite.hpp"

	Composite::Composite():
		name_{"default_composite"},
		shape_{}
		{}

	Composite::Composite(std::string name):
		name_{name},
		shape_{}
		{}

	void Composite::add(std::shared_ptr<Shape> const& shape)
	{
		shapes_.push_back(shape);
	}

	std::vector<std::shared_ptr<Shape>> get_children() const
	{
		return shape_;
	}

	Hit Composite::intersect(Ray const& ray) const
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
