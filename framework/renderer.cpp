// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render()
{
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

Hit Renderer::closest_hit(Ray const& ray)
{
  Hit closest_hit;
  Hit temp_hit;

  for(auto& comp : scene_.shapes_)
  {
    temp_hit = comp -> intersect(ray);

    if(temp_hit.t_ < closest_hit.t_)
    {
      closest_hit = temp_hit;
    }
  }

  return closest_hit;
}

void Renderer::ambient_light(Color & pixel_clr, Color const& ka)
{
  pixel_clr += (scene_.ambient_ * ka); 
}

void Renderer::point_light(Color & pixel_clr, std::shared_ptr<Light> const& light, Hit const& hit, Ray const& ray)
{
  glm::vec3 light_direction = glm::normalize((light -> pos_) - (hit.intersection_));

  Ray light_ray{hit.intersection_, light_direction};

  float distance = glm::length(hit.intersection_ - (light -> pos_));

  Hit light_hit = closest_hit(light_ray);

  if(light_hit.t_ > distance)
  {
    diffuse_light(pixel_clr, hit, light, light_ray);

    specular_light(pixel_clr, hit, light, light_ray, ray);
  }
}

void Renderer::diffuse_light(Color & pixel_clr, Hit const& hit, std::shared_ptr<Light> light, Ray const& light_ray)
{
  float factor = glm::dot(glm::normalize(hit.normal_), glm::normalize(light_ray.direction));

  pixel_clr += (light -> color_) * (hit.shape_ -> get_material() -> kd_) * std::max(factor, 0.0f);
}

void Renderer::specular_light(Color & pixel_clr, Hit const& hit, std::shared_ptr<Light> light, Ray const& light_ray, Ray const& ray)
{
  glm::vec3 reflection = glm::normalize(glm::reflect(light_ray.direction, hit.normal_));

  float factor = std::max(0.0f, glm::dot(reflection, glm::normalize(-(ray.direction))));

  pixel_clr += (light -> color_) * (hit.shape_ -> get_material() -> ks_) * pow(factor, hit.shape_ -> get_material() -> m_);
}

Color Renderer::tone_mapping(Color const& raytrace_color)
{
  Color final_color;

  final_color.r = (raytrace_color.r / (raytrace_color.r + 1));
  final_color.g = (raytrace_color.g / (raytrace_color.g + 1));
  final_color.b = (raytrace_color.b / (raytrace_color.b + 1));

  return final_color;
}