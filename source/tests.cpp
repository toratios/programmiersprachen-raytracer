#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <box.cpp>
#include <sphere.cpp>

TEST_CASE ("default constructor box", "[aufgabe 5.2]"){
  Box b;
  glm::vec3 min = b.get_min();
  glm::vec3 max = b.get_max();
  REQUIRE(min.x == 0.0f);
  REQUIRE(min.y == 0.0f);
  REQUIRE(min.z == 0.0f);
  REQUIRE(max.x == 1.0f);
  REQUIRE(max.y == 1.0f);
  REQUIRE(max.z == 1.0f);
}

TEST_CASE ("user constructor box", "[aufgabe 5.2]"){
  Box b{glm::vec3{1.0,2.0,3.0},glm::vec3{4.0,5.0,6.0}};
  glm::vec3 min = b.get_min();
  glm::vec3 max = b.get_max();
  REQUIRE(min.x == 1.0f);
  REQUIRE(min.y == 2.0f);
  REQUIRE(min.z == 3.0f);
  REQUIRE(max.x == 4.0f);
  REQUIRE(max.y == 5.0f);
  REQUIRE(max.z == 6.0f);
}

TEST_CASE ("default constructor sphere", "[aufgabe 5.2]"){
  Sphere s;
  glm::vec3 center = s.get_center();
  REQUIRE(center.x == 0.0f);
  REQUIRE(center.y == 0.0f);
  REQUIRE(center.z == 0.0f);
  REQUIRE(s.get_r() == 1.0f);
}

TEST_CASE ("user constructor sphere", "[aufgabe 5.2]"){
  Sphere s{glm::vec3{1.0,2.0,3.0},4.0};
  glm::vec3 center = s.get_center();
  REQUIRE(center.x == 1.0f);
  REQUIRE(center.y == 2.0f);
  REQUIRE(center.z == 3.0f);
  REQUIRE(s.get_r() == 4.0f);
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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
