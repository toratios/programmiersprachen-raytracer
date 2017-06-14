#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <box.cpp>
#include <sphere.cpp>
#include <shape.cpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE ("default constructor box", "[aufgabe 5.2/5.3]"){
  Box b;
  glm::vec3 min = b.get_min();
  glm::vec3 max = b.get_max();
  REQUIRE(min.x == 0.0f);
  REQUIRE(min.y == 0.0f);
  REQUIRE(min.z == 0.0f);
  REQUIRE(max.x == 1.0f);
  REQUIRE(max.y == 1.0f);
  REQUIRE(max.z == 1.0f);
  REQUIRE(b.get_name() == "Box");
  Color col = b.get_color();
  REQUIRE(col.r == 1.0f);
  REQUIRE(col.g == 1.0f);
  REQUIRE(col.b == 1.0f);
}

TEST_CASE ("user constructor box", "[aufgabe 5.2/5.3]"){
  Box b{glm::vec3{1.0,2.0,3.0},glm::vec3{4.0,5.0,6.0},Color{1.0,0.5,0.0},"TestBox"};
  glm::vec3 min = b.get_min();
  glm::vec3 max = b.get_max();
  REQUIRE(min.x == 1.0f);
  REQUIRE(min.y == 2.0f);
  REQUIRE(min.z == 3.0f);
  REQUIRE(max.x == 4.0f);
  REQUIRE(max.y == 5.0f);
  REQUIRE(max.z == 6.0f);
  REQUIRE(b.get_name() == "TestBox");
  Color col = b.get_color();
  REQUIRE(col.r == 1.0f);
  REQUIRE(col.g == 0.5f);
  REQUIRE(col.b == 0.0f);
}

TEST_CASE ("default constructor sphere", "[aufgabe 5.2/5.3]"){
  Sphere s;
  glm::vec3 center = s.get_center();
  REQUIRE(center.x == 0.0f);
  REQUIRE(center.y == 0.0f);
  REQUIRE(center.z == 0.0f);
  REQUIRE(s.get_r() == 1.0f);
  REQUIRE(s.get_name() == "Sphere");
  Color col = s.get_color();
  REQUIRE(col.r == 1.0f);
  REQUIRE(col.g == 1.0f);
  REQUIRE(col.b == 1.0f);
}

TEST_CASE ("user constructor sphere", "[aufgabe 5.2/5.3]"){
  Sphere s{glm::vec3{1.0,2.0,3.0},4.0,Color{1.0,0.5,0.0},"TestSphere"};
  glm::vec3 center = s.get_center();
  REQUIRE(center.x == 1.0f);
  REQUIRE(center.y == 2.0f);
  REQUIRE(center.z == 3.0f);
  REQUIRE(s.get_r() == 4.0f);
  REQUIRE(s.get_name() == "TestSphere");
  Color col = s.get_color();
  REQUIRE(col.r == 1.0f);
  REQUIRE(col.g == 0.5f);
  REQUIRE(col.b == 0.0f);
}

TEST_CASE ("area box", "[aufgabe 5.2]"){
  Box b{glm::vec3{5.0},glm::vec3{1.0,1.0,6.0}};
  REQUIRE(b.area() == 48.0f);
}

TEST_CASE ("volume box", "[aufgabe 5.2]"){
  Box b{glm::vec3{5.0,5.0,6.0},glm::vec3{1.0,1.0,5.0}};
  REQUIRE(b.volume() == 16.0f);
}

TEST_CASE ("area sphere", "[aufgabe 5.2]"){
  Sphere s{glm::vec3{1.0},2.0};
  REQUIRE(s.area() == Approx(50.2655).epsilon(0.001));
}

TEST_CASE ("volume sphere", "[aufgabe 5.2]"){
  Sphere s{glm::vec3{1.0},2.0};
  REQUIRE(s.volume()== Approx(33.5103).epsilon(0.001));
}

TEST_CASE ("print box", "[aufgabe 5.5]"){
  Box b;
  b.print(std::cout);
  std::cout << "\n";
}

TEST_CASE ("print sphere", "[aufgabe 5.5]"){
  Sphere s;
  std::cout << "\n";
  s.print(std::cout);
}
/*
TEST_CASE ("intersectRaySphere", "[intersect]"){
  //Ray
  glm::vec3 ray_origin{0.0,0.0,0.0};
  //ray direction has to be normalized !
  //you can use:
  //v = glm::normalize(some_vector)
  glm::vec3 ray_direction{0.0,0.0,1.0};

  //Sphere
  glm::vec3 sphere_center{0.0,0.0,5.0};
  float sphere_radius{1.0};

  float distance{0.0};
  auto result = glm::intersectRaySphere(
    ray_origin, ray_direction,
    sphere_center,
    sphere_radius * sphere_radius, // squared radius !!!
    distance);
  REQUIRE (distance == Approx(4.0f));
}*/

TEST_CASE ("intersectRaySphereAgain", "[aufgabe 5.6]"){
  Sphere s{glm::vec3{5.0},1.0};
  Ray r{glm::vec3{0.0},glm::vec3{1.0}};

  REQUIRE (s.intersect(r,0.0) == true);

  Ray r2{glm::vec3{0.0},glm::vec3{-1.0}};

  REQUIRE (s.intersect(r2,0.0) == false);
}

TEST_CASE ("blablabla", "[aufgabe 5.8]"){
  Color red (255,0,0);
  glm::vec3 position(0.0);
  Sphere* s1 = new Sphere(position, 1.2, red, "sphere0");
  Shape* s2 = new Sphere(position, 1.2, red, "sphere1");
  s1 -> print(std::cout);
  s2 -> print(std::cout);
  delete s1;
  delete s2;
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
