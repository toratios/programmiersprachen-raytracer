#include "composite.hpp"
#include <memory>

	Composite::Composite():
		name_{"default_composite"},
		shape_{}
		{}

	Composite::Composite(std::string name):
		name_{name},
		shape_{}
		{}

	void Composite::add(std::shared_ptr<Shape> shape)
	{
		shapes_.insert(shape -> name_, shape);
	}

	void Composite::remove(std::string name)
	{
		shapes_.erase(name);
	}

	std::map<std::string, std::shared_ptr<Shape>> get_children() const
	{
		return shape_;
	}