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
#include <triangle.hpp>
#include <triangle.cpp>
#include <cone.cpp>
#include <cylinder.cpp>

#include <sdfloader.cpp>

int main(int argc, char* argv[])
{
//=================Erstellen der Scene===================================================

  Camera test_cam{"test_cam", 110.0f};

  glm::vec3 eye{0.0f,0.0f,0.0f};
  test_cam.set_eye(eye);

  glm::mat4x4 testtrans = test_cam.get_transformation();
  glm::mat4x4 testtransinv = test_cam.get_transformation_inv();

  std::cout << glm::to_string(testtrans) << "\n";

  std::cout << glm::to_string(testtransinv) << "\n";

  test_cam.rotate(30.0f,glm::vec3{0.0,0.0,1.0});
  test_cam.translate(glm::vec3{0.0,0.0,-50.0});

  glm::mat4x4 testtrans2 = test_cam.get_transformation();
  glm::mat4x4 testtransinv2 = test_cam.get_transformation_inv();

  std::cout << glm::to_string(testtrans2) << "\n";

  std::cout << glm::to_string(testtransinv2) << "\n";

  std::cout << glm::to_string(test_cam.get_eye()) << "\n";

  Ray testray{glm::vec3{10.0}, glm::vec3{100.0, 200.0, 300.0}};

  std::cout << glm::to_string(testray.origin);
  
      testray.origin = glm::vec3(test_cam.get_transformation_inv() * glm::vec4(0.0, 0.0, 0.0, 1.0));
      testray.direction = glm::vec3(test_cam.get_transformation_inv() * (glm::vec4(100.0, 200.0, 300.0, 0.0)));

  std::cout << glm::to_string(testray.direction);

  Scene test_scene{Color{0.1f,0.1f,0.1f}, test_cam};

//=================Lights================================================================
  std::shared_ptr<Light> test_light_1 = std::make_shared<Light>
        ("test_light_1", glm::vec3{2000.0f, 750.0f, -700.0f}, Color{1.0f,1.0f,1.0f});

  std::shared_ptr<Light> test_light_2 = std::make_shared<Light>
        ("test_light_2", glm::vec3{500.0f, 1500.0f, -800.0f}, Color{1.0f,1.0f,1.0f});

  std::shared_ptr<Light> test_light_3 = std::make_shared<Light>
        ("test_light_3", glm::vec3{0.0f, 1500.0f, -800.0f}, Color{1.0f,1.0f,1.0f});

  std::shared_ptr<Light> test_light_4 = std::make_shared<Light>
        ("test_light_4", glm::vec3{0.0f,100.0f,0.0f}, Color{1.0f,1.0f,1.0f});

  std::vector<std::shared_ptr<Light>> lights;

  lights.push_back(test_light_1);
  lights.push_back(test_light_2);
  lights.push_back(test_light_3);
  lights.push_back(test_light_4);

  test_scene.lights_ = lights;

//=================Materials=============================================================
  std::map<std::string, std::shared_ptr<Material>> materials;

  std::shared_ptr<Material> test_material_1 = std::make_shared<Material>
        ("test_material_1",Color{0.8f,0.7f,0.1f}, Color{0.8f,0.7f,0.1f}, Color{0.8f,0.7f,0.1f}, 200.0f, 0.1f);

  std::shared_ptr<Material> test_material_2 = std::make_shared<Material>
        ("test_material_2",Color{0.1f,0.8f,0.7f}, Color{0.1f,0.8f,0.7f}, Color{0.1f,0.8f,0.7f}, 200.0f, 0.3f);

  std::shared_ptr<Material> test_material_4 = std::make_shared<Material>
        ("test_material_4",Color{0.7f,0.1f,8.0f}, Color{0.7f,0.1f,1.0f}, Color{0.7f,0.1f,1.0f}, 500.0f, 0.2f);

  std::shared_ptr<Material> test_material_3 = std::make_shared<Material>
        ("test_material_3",Color{1.0f,1.0f,1.0f}, Color{1.0f,1.0f,1.0f}, Color{1.0f,1.0f,1.0f}, 0.2f, 0.0f);

  std::shared_ptr<Material> test_material_5 = std::make_shared<Material>
        ("test_material_5",Color{0.05f,0.05f,0.05f}, Color{0.05f,0.05f,0.05f}, Color{0.05f,0.05f,0.05f}, 0.0f, 0.0f);

  std::shared_ptr<Material> test_material_6 = std::make_shared<Material>
        ("test_material_6",Color{1.0f,1.0f,1.0f}, Color{1.0f,1.0f,1.0f}, Color{1.0f,1.0f,1.0f}, 1000.0f, 0.0f, 0.1f, 1.5f);


  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_1", test_material_1));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_2", test_material_2));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_3", test_material_3));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_4", test_material_4));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_5", test_material_5));
  materials.insert(std::pair<std::string, std::shared_ptr<Material>>("test_material_6", test_material_6));

  test_scene.materials_ = materials;

//=================Shapes & Composites===================================================
//=================Floor=================================================================

  std::shared_ptr<Shape> test_box_1 = std::make_shared<Box>
    (glm::vec3{-1000.0f,300.0f,-500.0f},glm::vec3{0.0f,300.0f,-1000.0f},
     test_material_5, "test_box_1");

  std::shared_ptr<Shape> test_box_1_1 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-260.0f,-500.0f},glm::vec3{-500.0f,-259.0f,-750.0f},
     test_material_5, "test_box_1");
  std::shared_ptr<Shape> test_box_1_2 = std::make_shared<Box>
    (glm::vec3{-500.0f,-260.0f,-500.0f},glm::vec3{0.0f,-259.0f,-750.0f},
     test_material_3, "test_box_1");
  std::shared_ptr<Shape> test_box_1_3 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-260.0f,-750.0f},glm::vec3{-500.0f,-259.0f,-1000.0f},
     test_material_3, "test_box_1");
  std::shared_ptr<Shape> test_box_1_4 = std::make_shared<Box>
    (glm::vec3{-500.0f,-260.0f,-750.0f},glm::vec3{0.0f,-259.0f,-1000.0f},
     test_material_5, "test_box_1");

  std::shared_ptr<Shape> test_box_2 = std::make_shared<Box>
    (glm::vec3{0.0f,300.0f,-500.0f},glm::vec3{1000.0f,300.0f,-1000.0f},
     test_material_3, "test_box_2");

  std::shared_ptr<Shape> test_box_2_1 = std::make_shared<Box>
    (glm::vec3{0.0f,-260.0f,-500.0f},glm::vec3{500.0f,-259.0f,-750.0f},
     test_material_5, "test_box_1");
  std::shared_ptr<Shape> test_box_2_2 = std::make_shared<Box>
    (glm::vec3{500.0f,-260.0f,-500.0f},glm::vec3{1000.0f,-259.0f,-750.0f},
     test_material_3, "test_box_1");
  std::shared_ptr<Shape> test_box_2_3 = std::make_shared<Box>
    (glm::vec3{0.0f,-260.0f,-750.0f},glm::vec3{500.0f,-259.0f,-1000.0f},
     test_material_3, "test_box_1");
  std::shared_ptr<Shape> test_box_2_4 = std::make_shared<Box>
    (glm::vec3{500.0f,-260.0f,-750.0f},glm::vec3{1000.0f,-259.0f,-1000.0f},
     test_material_5, "test_box_1");

  std::shared_ptr<Shape> test_box_3 = std::make_shared<Box>
    (glm::vec3{-1000.0f,300.0f,-1000.0f},glm::vec3{0.0f,300.0f,-2000.0f},
     test_material_3, "test_box_3");

  std::shared_ptr<Shape> test_box_3_1 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-260.0f,-1000.0f},glm::vec3{-500.0f,-259.0f,-1250.0f},
     test_material_5, "test_box_1");
  std::shared_ptr<Shape> test_box_3_2 = std::make_shared<Box>
    (glm::vec3{-500.0f,-260.0f,-1000.0f},glm::vec3{0.0f,-259.0f,-1250.0f},
     test_material_3, "test_box_1");
  std::shared_ptr<Shape> test_box_3_3 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-260.0f,-1250.0f},glm::vec3{-500.0f,-259.0f,-1500.0f},
     test_material_3, "test_box_1");
  std::shared_ptr<Shape> test_box_3_4 = std::make_shared<Box>
    (glm::vec3{-500.0f,-260.0f,-1250.0f},glm::vec3{0.0f,-259.0f,-1500.0f},
     test_material_5, "test_box_1");

  std::shared_ptr<Shape> test_box_4 = std::make_shared<Box>
    (glm::vec3{-0.0f,300.0f,-1000.0f},glm::vec3{1000.0f,300.0f,-2000.0f},
     test_material_5, "test_box_4");

  std::shared_ptr<Shape> test_box_4_1 = std::make_shared<Box>
    (glm::vec3{0.0f,-260.0f,-1000.0f},glm::vec3{500.0f,-259.0f,-1250.0f},
     test_material_5, "test_box_1");
  std::shared_ptr<Shape> test_box_4_2 = std::make_shared<Box>
    (glm::vec3{500.0f,-260.0f,-1000.0f},glm::vec3{1000.0f,-259.0f,-1250.0f},
     test_material_3, "test_box_1");
  std::shared_ptr<Shape> test_box_4_3 = std::make_shared<Box>
    (glm::vec3{0.0f,-260.0f,-1250.0f},glm::vec3{500.0f,-259.0f,-1500.0f},
     test_material_3, "test_box_1");
  std::shared_ptr<Shape> test_box_4_4 = std::make_shared<Box>
    (glm::vec3{500.0f,-260.0f,-1250.0f},glm::vec3{1000.0f,-259.0f,-1500.0f},
     test_material_5, "test_box_1");

//=================Objects===============================================================
 
  std::shared_ptr<Shape> test_box_5 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-260.0f,-500.0f},glm::vec3{-1000.0f,2000.0f,-1500.0f},
     test_material_3, "test_box_5");

  std::shared_ptr<Shape> test_box_6 = std::make_shared<Box>
    (glm::vec3{-1000.0f,-260.0f,-1500.0f},glm::vec3{1000.0f,2000.0f,-1500.0f},
     test_material_3, "test_box_6");



  std::shared_ptr<Shape> test_sphere_1 = std::make_shared<Sphere>
    (glm::vec3{130.0f,0.0f,-1100.0f}, 200.0f, test_material_1, "test_sphere_1");

  std::shared_ptr<Shape> test_sphere_2 = std::make_shared<Sphere>
    (glm::vec3{-200.0f,50.0f,-850.0f}, 200.0f, test_material_2, "test_sphere_2");

  std::shared_ptr<Shape> test_sphere_3 = std::make_shared<Sphere>
    (glm::vec3{295.0f,-130.0f,-800.0f}, 120.0f, test_material_4, "test_sphere_3");

  std::shared_ptr<Shape> test_sphere_4 = std::make_shared<Sphere>
    (glm::vec3{100.0f,100.0f,-400.0f}, 300.0f, test_material_6, "test_sphere_4");

    /*
  std::shared_ptr<Shape> test_triangle_1 = std::make_shared<Triangle>
    (glm::vec3{-1000.0f,100.0f,-1400.0f},
      glm::vec3{0.0f,600.0f,-700.0f},
      glm::vec3{1000.0f,200.0f,-1200.0f},
      test_material_4, "test_triangle_1");

  std::shared_ptr<Shape> test_triangle_2 = std::make_shared<Triangle>
    (glm::vec3{700.0f,-200.0f,-900.0f},
      glm::vec3{450.0f,200.0f,-750.0f},
      glm::vec3{600.0f,-200.0f,-600.0f},
      test_material_1, "test_triangle_2");


  std::shared_ptr<Shape> test_cylinder_1 = std::make_shared<Cylinder>
    (glm::vec3{500.0f,-200.0f,700.0f}, 200.0f, 400.0f, test_material_1, "test_cylinder_1");
      */

  std::vector<std::shared_ptr<Shape>> shapes;

  //shapes.push_back(test_box_1);
  shapes.push_back(test_box_1_1);
  shapes.push_back(test_box_1_2);
  shapes.push_back(test_box_1_3);
  shapes.push_back(test_box_1_4);
  //shapes.push_back(test_box_2);
  shapes.push_back(test_box_2_1);
  shapes.push_back(test_box_2_2);
  shapes.push_back(test_box_2_3);
  shapes.push_back(test_box_2_4);
  //shapes.push_back(test_box_3);
  shapes.push_back(test_box_3_1);
  shapes.push_back(test_box_3_2);
  shapes.push_back(test_box_3_3);
  shapes.push_back(test_box_3_4);
  //shapes.push_back(test_box_4);
  shapes.push_back(test_box_4_1);
  shapes.push_back(test_box_4_2);
  shapes.push_back(test_box_4_3);
  shapes.push_back(test_box_4_4);





  //shapes.push_back(test_box_5);
  //shapes.push_back(test_box_6);
  shapes.push_back(test_sphere_1);
  shapes.push_back(test_sphere_2);
  shapes.push_back(test_sphere_3);
  //shapes.push_back(test_sphere_4);

  //shapes.push_back(test_triangle_1);
  //shapes.push_back(test_cylinder_1);



  std::shared_ptr<Composite> test_composite = std::make_shared<Composite>
                                              ("test_composite", shapes);

  std::vector<std::shared_ptr<Composite>> composites;

  composites.push_back(test_composite);

  test_scene.shapes_ = composites;


//=================Renderer==============================================================

  unsigned const width = 1000;
  unsigned const height = 1000;

  //unsigned const width = 3840;
  //unsigned const height = 2160;

  std::string const filename = "./test_rotation_7.ppm";
  
  Renderer test_renderer{width, height, filename, test_scene};

  std::thread thr([&test_renderer]() { test_renderer.render_scene(); });

  thr.join();
  
  return 0;

}