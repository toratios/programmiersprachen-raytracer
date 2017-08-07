#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

#include <map>
#include <memory>
#include <string>

#include "shape.hpp"
#include "box.hpp"
#include "sphere.hpp"

class Composite : Shape
{

public:

	Composite();

	Composite(std::string name);

	void add(std::shared_ptr<Shape> shape);

	void remove(std::string name);

	std::map<std::string, std::shared_ptr<Shape>> get_children() const;

private:

	std::string name_;

	std::map<std::string, std::shared_ptr<Shape>> shapes_;

};

#endif