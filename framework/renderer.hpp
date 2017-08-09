// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#define GLM_FORCE_RADIANS

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "hit.hpp"
#include "scene.hpp"
#include "composite.hpp"


class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene);

  void render();
  void write(Pixel const& p);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

  void render_scene();
  Color raytrace(Ray const& ray) const;
  Hit closest_hit(Ray const& ray) const;
  Color ambient(Color const& ka) const;
  Color point_light(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& ray) const;
  bool shadow(Ray const& shadow_ray) const;
  Color diffuse(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& light_ray) const;
  Color specular(std::shared_ptr<Light> const& light, Hit const& hit,Ray const& ray, Ray const& light_ray) const;
  Color reflection() const;
  Color refraction() const;
  Color tone_mapping(Color const& color) const;
  
private:
  Scene scene_;
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
