#include <renderer.hpp>
#include <window.hpp>
#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include <scene.hpp>
#include <hit.cpp>
#include <color.hpp>
#include <renderer.hpp>
#include <box.cpp>
#include <sphere.cpp>
#include <shape.cpp>
#include <composite.hpp>
#include <camera.hpp>
#include <light.hpp>
#include <material.hpp>
#include <pixel.hpp>
#include <ray.hpp>
#include <ppmwriter.hpp>
#include <vector>
#include <memory>
#include <map>
#include <glm/glm.hpp>
#include <string>

int main(int argc, char* argv[])
{
//=================Erstellen der Scene===================================================

  Camera test_cam{"test_cam", 100.0f};

  Scene test_scene{Color{1.0f,1.0f,1.0f}, test_cam};

//=================Lights================================================================
  std::shared_ptr<Light> test_light_1 = std::make_shared<Light>
        ("test_light_1", glm::vec3{0.0f, 0.0f, 0.0f}, Color{1.0f,1.0f,1.0f});

  std::shared_ptr<Light> test_light_2 = std::make_shared<Light>
        ("test_light_2", glm::vec3{0.0f, 1000.0f, -200.0f}, Color{1.0f,1.0f,1.0f});

  std::shared_ptr<Light> test_light_3 = std::make_shared<Light>
        ("test_light_3", glm::vec3{0.0f, 3000.0f, -1550.0f}, Color{1.0f,1.0f,1.0f});

  std::vector<std::shared_ptr<Light>> lights;

  lights.push_back(test_light_1);
  lights.push_back(test_light_2);
  lights.push_back(test_light_3);

  test_scene.lights_ = lights;

//=================Materials=============================================================
  std::map<std::string, std::shared_ptr<Material>> materials;

  std::shared_ptr<Material> test_material_1 = std::make_shared<Material>
        ("test_material_1",Color{1.0f,0.0f,0.0f}, Color{1.0f,0.0f,0.0f}, Color{1.0f,0.0f,0.0f}, 20.0f);

  std::shared_ptr<Material> test_material_2 = std::make_shared<Material>
        ("test_material_2",Color{1.0f,1.0f,0.0f}, Color{1.0f,1.0f,0.0f}, Color{1.0f,0.0f,0.0f}, 500.0f);

  std::shared_ptr<Material> test_material_3 = std::make_shared<Material>
        ("test_material_3",Color{0.09f,0.09f,0.09f}, Color{0.09f,0.09f,0.09f}, Color{0.09f,0.09f,0.09f}, 500.0f);

  std::shared_ptr<Material> test_material_4 = std::make_shared<Material>
        ("test_material_4",Color{0.0f,0.0f,1.0f}, Color{0.0f,0.0f,1.0f}, Color{0.0f,0.0f,1.0f}, 20.0f);

  std::shared_ptr<Material> test_material_5 = std::make_shared<Material>
        ("test_material_5",Color{0.01f,0.01f,0.01f}, Color{0.01f,0.01f,0.01f}, Color{0.01f,0.01f,0.01f}, 500.0f);


  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_1", test_material_1));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_2", test_material_2));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_3", test_material_3));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_4", test_material_4));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_5", test_material_5));

  test_scene.materials_ = materials;

//=================Shapes & Composites===================================================

  std::shared_ptr<Shape> test_box_1 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-280.0f,-500.0f},glm::vec3{0.0f,-259.0f,-1000.0f},
     test_material_5, "test_box_1");
/*
  std::shared_ptr<Shape> test_box_1_1 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-260.0f,-500.0f},glm::vec3{500.0f,-259.0f,-750.0f},
     test_material_5, "test_box_1");
  std::shared_ptr<Shape> test_box_1_2 = std::make_shared<Box>
    (glm::vec3{-500.0f,-260.0f,-500.0f},glm::vec3{0.0f,-259.0f,-750.0f},
     test_material_5, "test_box_1");
  std::shared_ptr<Shape> test_box_1_3 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-260.0f,-750.0f},glm::vec3{500.0f,-259.0f,-1000.0f},
     test_material_5, "test_box_1");
  std::shared_ptr<Shape> test_box_1_4 = std::make_shared<Box>
    (glm::vec3{-500.0f,-260.0f,-750.0f},glm::vec3{0.0f,-259.0f,-1000.0f},
     test_material_5, "test_box_1");
*/
  std::shared_ptr<Shape> test_box_2 = std::make_shared<Box>
    (glm::vec3{0.0f,-280.0f,-500.0f},glm::vec3{1000.0f,-259.0f,-1000.0f},
     test_material_3, "test_box_2");

  std::shared_ptr<Shape> test_box_3 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-280.0f,-1000.0f},glm::vec3{0.0f,-259.0f,-2000.0f},
     test_material_3, "test_box_3");

  std::shared_ptr<Shape> test_box_4 = std::make_shared<Box>
    (glm::vec3{-0.0f,-280.0f,-1000.0f},glm::vec3{1000.0f,-259.0f,-2000.0f},
     test_material_5, "test_box_4");

  std::shared_ptr<Shape> test_box_5 = std::make_shared<Box>
    (glm::vec3{100.0f,500.0f,-800.0f},glm::vec3{200.0f,700.0f,-1000.0f},
     test_material_1, "test_box_5");



  std::shared_ptr<Shape> test_sphere_1 = std::make_shared<Sphere>
    (glm::vec3{-70.0f,0.0f,-1000.0f}, 200.0f, test_material_1, "test_sphere_1");

  std::shared_ptr<Shape> test_sphere_2 = std::make_shared<Sphere>
    (glm::vec3{-500.0f,200.0f,-750.0f}, 200.0f, test_material_2, "test_sphere_2");

  std::shared_ptr<Shape> test_sphere_3 = std::make_shared<Sphere>
    (glm::vec3{400.0f,400.0f,-800.0f}, 100.0f, test_material_4, "test_sphere_3");

  std::shared_ptr<Shape> test_sphere_4 = std::make_shared<Sphere>
    (glm::vec3{200.0f,200.0f,-1300.0f}, 200.0f, test_material_2, "test_sphere_4");


  std::vector<std::shared_ptr<Shape>> shapes;

  shapes.push_back(test_box_1);
  //shapes.push_back(test_box_1_1);
  //shapes.push_back(test_box_1_2);
  //shapes.push_back(test_box_1_3);
  //shapes.push_back(test_box_1_4);
  shapes.push_back(test_box_2);
  shapes.push_back(test_box_3);
  shapes.push_back(test_box_4);
  shapes.push_back(test_box_5);


  shapes.push_back(test_sphere_1);
  shapes.push_back(test_sphere_2);
  shapes.push_back(test_sphere_3);
  shapes.push_back(test_sphere_4);

  std::shared_ptr<Composite> test_composite = std::make_shared<Composite>
                                              ("test_composite", shapes);

  std::vector<std::shared_ptr<Composite>> composites;

  composites.push_back(test_composite);

  test_scene.shapes_ = composites;


//=================Renderer==============================================================

  unsigned const width = 1000;
  unsigned const height = 700;

  std::string const filename = "./test_.ppm";

  Renderer test_renderer{width, height, filename, test_scene};

  std::thread thr([&test_renderer]() { test_renderer.render_scene(); });

  thr.join();

  return 0;

}