#define CATCH_CONFIG_MAIN // This tells Catch to provide a main() - only do this
// in one cpp file
#include "../include/catch.hpp"

import vector;
#include <sstream>
#include <type_traits>

TEST_CASE("add two vectors3", "[vector3]") {

  math::vector3 vec1{3, 2, 1};
  math::vector3 vec2{6, 4, 2};

  REQUIRE((vec1 + vec1) == vec2);

  REQUIRE(vec1 + math::vector3{2, 1, -1} == math::vector3{5, 3, 0});

  REQUIRE((vec1.x == vec1.vec[0] && vec1.y == vec1.vec[1] &&
           vec1.z == vec1.vec[2]) == true);
}

TEST_CASE("sub two vectors3", "[vector3]") {

  math::vector3 vec1{3, 2, 1};
  math::vector3 vec2{6, 4, 2};

  REQUIRE(vec1 - math::vector3{2, 1, -1} == math::vector3{1, 1, 2});
}

TEST_CASE("print vectors3", "[vector3]") {

  math::vector3 vec1{3, 2, 1};
  std::ostringstream test_string{};
  test_string << vec1;

  REQUIRE(test_string.str() == std::string{"[3, 2, 1]"});
}

TEST_CASE("div two vectors3", "[vector3]") {

  math::vector3 vec1{3, 2, 1};
  math::vector3 vec2{std::array<int, 3>{1, 3, 2}};
  static_assert(std::is_same_v<decltype(vec1), math::vector3<int, float>>);

  REQUIRE(vec1 / math::vector3{2, 1, -1} == math::vector3{1, 2, -1});
}

TEST_CASE("mul two vectors3", "[vector3]") {

  math::vector3 vec1{ 3, 2, 1 };
  math::vector3 vec2{ 6, 4, 2 };

  REQUIRE(vec1 * vec2 == math::vector3{ 18, 8, 2 });
}

TEST_CASE("magnitude of vector3<int, float>", "[vector3]") {

  math::vector3 vec1{ 1, 2, 2 };

  REQUIRE(vec1.magnitude() == 3);
}

TEST_CASE("cross product of two vectors3<int, float>", "[vector3]") {

  math::vector3<int, float> vec1{ 3, 2, 1 };
  math::vector3 vec2{ 6, 4, 2 };
  static_assert(std::is_same_v<decltype(vec1.cross(vec2)), math::vector3<int, float>>);
  REQUIRE(vec1.cross(vec2) == math::vector3<int, float>{0,0,0});
}

TEST_CASE("dot product of two vectors3<int, float>", "[vector3]") {

  math::vector3<int, float> vec1{ 3, 2, 1 };
  math::vector3 vec2{ 6, 4, 2 };
  static_assert(std::is_same_v<decltype(vec1.cross(vec2)), math::vector3<int, float>>);
  REQUIRE(vec1.dot(vec2) == (18+8+2));
}

