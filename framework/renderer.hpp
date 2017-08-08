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
  Renderer(unsigned w, unsigned h, std::string const& file);

  void render();
  void write(Pixel const& p);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

  Hit closest_hit(Ray const& ray);

  void ambient_light(Color & clr, Color const& ka);

  void point_light(Color & pixel_clr, std::shared_ptr<Light> const& light, Hit const& hit, Ray const& ray);

  void diffuse_light(Color & clr, Hit const& hit, std::shared_ptr<Light> light, Ray const& light_ray);

  void specular_light(Color & pixel_clr, Hit const& hit, std::shared_ptr<Light> light, Ray const& light_ray, Ray const& ray);

  Color tone_mapping(Color const& color);


private:
  Scene scene_;
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
};

#endif // #ifndef BUW_RENDERER_HPP
