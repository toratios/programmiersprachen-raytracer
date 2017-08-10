// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
  : width_(w)
  , height_(h)
  , colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
  , filename_(file)
  , ppm_(width_, height_)
  , scene_{scene}
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

void Renderer::render_scene()
{
  float distance = (width_ / 2) / tan(scene_.camera_.get_fov() * M_PI / 360);

  float pos_y = (((float)height_) / -2);

  for(unsigned y = 0; y < height_; ++y)
  {
    float pos_x = (((float)width_) / -2);

    for(unsigned x = 0 ; x < width_; ++x)
    {
      Pixel pixel(x, y);

      Ray temp_ray = scene_.camera_.generate_ray(pos_x, pos_y, distance);

      Color temp_color = raytrace(temp_ray, 3);

      pixel.color = tone_mapping(temp_color);

      write(pixel);

      pos_x += 1.0f;
    }

    pos_y += 1.0f;
  }

  ppm_.save(filename_);
}

Color Renderer::raytrace(Ray const& ray, unsigned depth) const
{
  Hit hit = closest_hit(ray); 
     
  if(hit.hit_)
  {  
    Color pixel_clr = ambient(hit.shape_ -> get_material() -> ka_);      
            
    for(auto& light : scene_.lights_) 
    {
      pixel_clr += point_light(light, hit, ray);
    }

    if(depth > 0)
    {
      if((hit.shape_ -> get_material() -> kr_) > 0.0f)
      {
        pixel_clr = pixel_clr * (1.0f - (hit.shape_ -> get_material() -> kr_)) +
                    reflection(hit,ray, depth - 1) * (hit.shape_ -> get_material() -> kr_);
      }
    }

    return pixel_clr;   
  }

  return scene_.ambient_; 
}

Hit Renderer::closest_hit(Ray const& ray) const
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

Color Renderer::ambient(Color const& ka) const
{
  Color ambient_color;

  ambient_color = (scene_.ambient_ * ka);

  return ambient_color;
}

Color Renderer::point_light(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& ray) const
{
  Color point_light_color;

  glm::vec3 light_direction = glm::normalize((light -> pos_) - (hit.intersection_));

  Ray light_ray
  {
    hit.intersection_, 

    light_direction
  };

  Ray shadow_ray
  {
    hit.intersection_ + (0.01f * hit.normal_),

    light_direction
  };

  if(!shadow(shadow_ray))
  {
    point_light_color = (light -> color_) *
                      (diffuse(light, hit, light_ray) + specular(light, hit, ray, light_ray));
  }

  return point_light_color;
}

bool Renderer::shadow(Ray const& shadow_ray) const
{
  Hit shadow_hit = closest_hit(shadow_ray);

  if(shadow_hit.hit_)
  {
    return 1;
  }

  return 0;
}

Color Renderer::diffuse(std::shared_ptr<Light> const& light, Hit const& hit, Ray const& light_ray) const
{
  Color diffuse_color;

  float factor = glm::dot(glm::normalize(hit.normal_), glm::normalize(light_ray.direction));

  diffuse_color = (hit.shape_ -> get_material() -> kd_) * std::max(0.0f, factor);

  return diffuse_color;
}


Color Renderer::specular(std::shared_ptr<Light> const& light, Hit const& hit,Ray const& ray, Ray const& light_ray) const
{
  Color specular_color;

  glm::vec3 reflection = glm::normalize(glm::reflect(-(light_ray.direction), hit.normal_));

  float factor = std::max(0.0f, glm::dot(reflection, glm::normalize(-(ray.direction))));

  specular_color = (hit.shape_ -> get_material() -> ks_) * pow(factor, hit.shape_ -> get_material() -> m_);

  return specular_color;
}

Color Renderer::reflection(Hit const& hit, Ray const& ray, unsigned depth) const
{
  Color reflection_color;

  glm::vec3 reflection = glm::normalize(glm::reflect(ray.direction, hit.normal_));

  Ray reflection_ray
  {
    hit.intersection_ + (0.01f * reflection),

    reflection
  };

  reflection_color = raytrace(reflection_ray, depth - 1);

  return reflection_color;
}

Color Renderer::refraction(unsigned depth) const
{

}

Color Renderer::tone_mapping(Color const& raytrace_color) const
{
  Color final_color;

  final_color.r = (raytrace_color.r / (raytrace_color.r + 1));
  final_color.g = (raytrace_color.g / (raytrace_color.g + 1));
  final_color.b = (raytrace_color.b / (raytrace_color.b + 1));

  return final_color;
}

