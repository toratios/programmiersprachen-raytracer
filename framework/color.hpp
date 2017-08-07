// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
	float r;
  	float g;
  	float b;


  	Color():
  		r{0.0f},
  		g{0.0f},
  		b{0.0f}
  		{}

	Color(float red, float green, float blue): 
		r{red}, 
		g{green}, 
		b{blue} 
		{}


	Color& operator=(Color const& other)
	{
		r = other.r;
		g = other.g;
		b = other.b;
		return *this;
	}

  	Color& operator+=(Color const& other)
  	{
    	r += other.r;
    	g += other.g;
    	b += other.b;
    	return *this;
  	}

  	Color& operator-=(Color const& other)
  	{
    	r -= other.r;
    	g -= other.g;
    	b -= other.b;
    	return *this;
  	}

	Color& operator*=(Color const& other)
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		return *this;
	}

  	Color& operator*=(float other)
  	{
  		r *= other;
  		g *= other;
  		b *= other;
  		return *this;
  	}

  	friend Color operator+(Color const& a, Color const& b)
  	{
    	auto tmp(a);
    	tmp += b;
    	return tmp;
  	}

  	friend Color operator-(Color const& a, Color const& b)
  	{
    	auto tmp(a);
    	tmp -= b;
    	return tmp;
  	}

  	friend Color operator*(Color const& a, Color const& b)
  	{
  		auto tmp(a);
  		tmp *= b;
  		return tmp;
  	}

  	friend Color operator*(Color const& a, float b)
  	{
  		auto tmp(a);
  		tmp *= b;
  		return tmp;
  	}

  	friend std::ostream& operator<<(std::ostream& os, Color const& c)
  	{
    	os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    	return os;
  	}

  	friend bool operator==(Color const& a, Color const& b)
  	{
  		return ((a.r == b.r) && (a.g == b.g) && (a.b == b.b));	
  	}
};

#endif //#define BUW_COLOR_HPP
