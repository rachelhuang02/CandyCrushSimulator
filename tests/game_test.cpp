//
// Created by Rachel Huang on 5/3/21.
//

#include <catch2/catch.hpp>
#include <game.h>

using candy_crush::Game;
using candy_crush::Board;
using candy_crush::Candy;

Board CreateBoard2() {
    Board board({100, 100}, {160, 160}, 3);
    std::vector<std::vector<Candy>> candies;
    std::vector<Candy> row1;
    row1.push_back(Candy("pink", {110, 110}));
    row1.push_back(Candy("pink", {130, 110}));
    row1.push_back(Candy("skyblue", {150, 110}));
    candies.push_back(row1);
    std::vector<Candy> row2;
    row2.push_back(Candy("teal", {110, 130}));
    row2.push_back(Candy("skyblue", {130, 130}));
    row2.push_back(Candy("pink", {150, 130}));
    candies.push_back(row2);
    std::vector<Candy> row3;
    row3.push_back(Candy("teal", {110, 150}));
    row3.push_back(Candy("skyblue", {130, 150}));
    row3.push_back(Candy("purple", {150, 150}));
    candies.push_back(row3);
    board.setCandies(candies);
    return board;
}

TEST_CASE("Game is initialized correctly") {
    Board board = CreateBoard2();
    Game game(board, 50, 10);
    SECTION("Board is initialized properly") {
        glm::vec2 position = {110, 110};
        REQUIRE(board.GetCandyFromPosition(position).getColor() == "pink");
        REQUIRE(board.getCandies().size() == 3);
    }

    SECTION("Goal points is initialized properly") {
        REQUIRE(game.getGoalPoints() == 50);
    }

    SECTION("Time is initialized properly") {
        REQUIRE(game.getTimePerGame());
    }
}
