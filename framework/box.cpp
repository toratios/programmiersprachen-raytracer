#include "box.hpp"
#include <cmath>

Box::Box():
  Shape{"Box"},
  min_{glm::vec3{0.0f}},
  max_{glm::vec3{1.0f}} {}

Box::Box(glm::vec3 const& min, glm::vec3 const& max):
  Shape{"Box"},
  min_{min},
  max_{max} {sortMinMax();}
  
Box::Box(glm::vec3 const& min, glm::vec3 const& max, std::shared_ptr<Material> const& mat, std::string const& name):
  Shape{mat, name},
  min_{min},
  max_{max} {sortMinMax();}

glm::vec3 const& Box::get_min() const{
  return min_;
}

glm::vec3 const& Box::get_max() const{
  return max_;
}

void Box::sortMinMax(){
  float temp;

  if(min_.x > max_.x){
    temp = min_.x;
    min_.x = max_.x;
    max_.x = temp;
  }
  if(min_.y > max_.y){
    temp = min_.y;
    min_.y = max_.y;
    max_.y = temp;
  }
  if(min_.z > max_.z){
    temp = min_.z;
    min_.z = max_.z;
    max_.z = temp;
  }
}
  
float Box::area() const{
  float x = max_.x - min_.x;
  float y = max_.y - min_.y;
  float z = max_.z - min_.z;
  return (x*y*2+x*z*2+y*z*2);
}

float Box::volume() const{
  float volume = (max_.x - min_.x)*(max_.y - min_.y)*(max_.z - min_.z);
  return volume;
}

std::ostream& Box::print(std::ostream& os) const{
  Shape::print(os);
  os << "Min: " << "(" << min_.x << "," << min_.y << "," << min_.z << ")" << "\n" 
     << "Min: " << "(" << max_.x << "," << max_.y << "," << max_.z << ")";
  return os; 
}

Hit Box::intersect(Ray const& inray){
  float hit_x = 0.0;
  float hit_y = 0.0;
  float hit_z = 0.0;
  float dis = 0.0;
  Hit boxhit;
  Ray ray;
  ray.direction = glm::normalize(inray.direction);
  ray.origin = inray.origin;


  glm::vec3 hitvec{glm::vec3{0.0}};

  if(ray.origin.x <= min_.x || (ray.origin.x > min_.x && ray.origin.x < max_.x && ray.direction.x < 0)){
    hitvec.x = min_.x;  
  }
  else if(ray.origin.x >= max_.x || (ray.origin.x > min_.x && ray.origin.x < max_.x && ray.direction.x > 0)){
    hitvec.x = max_.x;  
  }

  if(ray.origin.y <= min_.y || (ray.origin.y > min_.y && ray.origin.y < max_.y && ray.direction.y < 0)){
    hitvec.y = min_.y;  
  }
  else if(ray.origin.y >= max_.y || (ray.origin.y > min_.y && ray.origin.y < max_.y && ray.direction.y > 0)){
    hitvec.y = max_.y;  
  }

  if(ray.origin.z <= min_.z || (ray.origin.z > min_.z && ray.origin.z < max_.z && ray.direction.z < 0)){
    hitvec.z = min_.z;  
  }
  else if(ray.origin.z >= max_.z || (ray.origin.z > min_.z && ray.origin.z < max_.z && ray.direction.z > 0)){
    hitvec.z = max_.z;  
  }

  dis = (hitvec.x - ray.origin.x)/ray.direction.x;
  hit_y = ray.origin.y + dis*ray.direction.y;
  hit_z = ray.origin.z + dis*ray.direction.z;;
  
  if(hit_y >= min_.y && hit_y <= max_.y && hit_z >= min_.z && hit_z <= max_.z && dis >= 0){
    boxhit.hit_ = true;
    boxhit.t_ = dis;
    boxhit.intersection_ = ray.origin + ray.direction * boxhit.t_;
    if(hitvec.x == min_.x){
      boxhit.normal_ = glm::vec3{-1.0,0.0,0.0};
      }
    else{
      boxhit.normal_ = glm::vec3{1.0,0.0,0.0};
    }
    boxhit.shape_ = this;
    return boxhit;
  }

  dis = (hitvec.y - ray.origin.y)/ray.direction.y;
  hit_x = ray.origin.x + dis*ray.direction.x;
  hit_z = ray.origin.z + dis*ray.direction.z;;
  
  if(hit_x >= min_.x && hit_x <= max_.x && hit_z >= min_.z && hit_z <= max_.z && dis >= 0){
    boxhit.hit_ = true;
    boxhit.t_ = dis;
    boxhit.intersection_ = ray.origin + ray.direction * boxhit.t_;
    if(hitvec.y == min_.y){
      boxhit.normal_ = glm::vec3{0.0,-1.0,0.0};
      }
    else{
      boxhit.normal_ = glm::vec3{0.0,1.0,0.0};
    }
    boxhit.shape_ = this;    
    return boxhit;
  }

  dis = (hitvec.z - ray.origin.z)/ray.direction.z;
  hit_x = ray.origin.x + dis*ray.direction.x;
  hit_y = ray.origin.y + dis*ray.direction.y;;
  
  if(hit_x >= min_.x && hit_x <= max_.x && hit_y >= min_.y && hit_y <= max_.y && dis >= 0){
    boxhit.hit_ = true;
    boxhit.t_ = dis;
    boxhit.intersection_ = ray.origin + ray.direction * boxhit.t_;
    if(hitvec.z == min_.z){
      boxhit.normal_ = glm::vec3{0.0,0.0,-1.0};
      }
    else{
      boxhit.normal_ = glm::vec3{0.0,0.0,1.0};
    }
    boxhit.shape_ = this;
    return boxhit;
  }

  boxhit.hit_ = false;
  return boxhit;
}
