#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <vector>
#include <memory>
#include <string>

#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "hit.hpp"

class Composite : public Shape
{

public:

	Composite();

	Composite(std::string name);
	

	void add(std::shared_ptr<Shape> const& shape);

	std::vector<std::shared_ptr<Shape>> get_children() const;

	Hit intersect(Ray const& ray) override;

private:

	std::string name_;

	std::vector<std::shared_ptr<Shape>> shapes_;

};

#endif