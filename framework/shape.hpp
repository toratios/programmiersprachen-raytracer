#ifndef SHAPE_HPP
#define SHAPE_HPP
#define GLM_FORCE_RADIANS
#include <memory>
#include "material.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include "glm/mat4x4.hpp"
#include "glm/vec3.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

class Hit;

class Shape{


public:

    Shape();
    Shape(std::string const& name);
    Shape(std::shared_ptr<Material> const& mat, std::string const& name);
    virtual ~Shape();

    std::shared_ptr<Material> const& get_material() const;
    std::string const& get_name() const;

    virtual std::ostream& print(std::ostream& os) const;
    //virtual float area() const = 0;
    //virtual float volume() const = 0;
    virtual Hit intersect(Ray const& ray) = 0;


    glm::mat4 const& get_transf() const;
    glm::mat4 const& get_inv() const;
    glm::mat4 const& get_inv_transp() const;
    bool is_transf() const;

    virtual void scale(glm::vec3 const& scale_vec);
    virtual void rotate(float angle, glm::vec3 const& rotation_vec);
    virtual void translate(glm::vec3 const& transl_vec);

private:

    std::shared_ptr<Material> mat_;
    std::string name_;

    glm::mat4 world_transformation_;
    glm::mat4 world_transformation_inv_;
    glm::mat4 world_transformation_inv_transp_;
    bool transf_;

};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif