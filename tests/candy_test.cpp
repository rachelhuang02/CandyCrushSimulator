//
// Created by Rachel Huang on 4/18/21.
//

#include <catch2/catch.hpp>
#include <candy.h>

using candy_crush::Candy;

TEST_CASE("Candy is initialized correctly") {
    Candy candy("pink", {100, 100});
    SECTION("Correct color") {
        REQUIRE(candy.getColor() == "pink");
    }
    SECTION("Correct position") {
        REQUIRE(candy.getPosition() == glm::vec2(100, 100));
    }
}

TEST_CASE("Correct shape is initialized given color") {
    SECTION("Pink candy") {
        Candy candy("pink", {100, 100});
        REQUIRE(candy.getShape() == "circle");
    }
    SECTION("Green Candy") {
        Candy candy("teal", {100, 100});
        REQUIRE(candy.getShape() == "triangle");
    }
    SECTION("Skyblue Candy") {
        Candy candy("skyblue", {100, 100});
        REQUIRE(candy.getShape() == "ellipse");
    }
    SECTION("Purple Candy") {
        Candy candy("purple", {100, 100});
        REQUIRE(candy.getShape() == "square");
    }
}