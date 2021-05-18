//#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <board.h>
#include <candy.h>

using candy_crush::Board;
using candy_crush::Candy;

Board CreateBoard() {
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

TEST_CASE("Class variables initialized correctly") {
    Board board({100, 100}, {200, 200}, 5);
    SECTION("Correct coordinates") {
        REQUIRE(board.getTopLeftCoordinate() == glm::vec2(100,100));
        REQUIRE(board.getBottomRightCoordinate() == glm::vec2(200,200));
    }
    SECTION("Correct candies per row") {
        REQUIRE(board.getCandiesPerRow() == 5);
    }
    SECTION("Correct size of cell") {
        REQUIRE(board.getSizeOfCell() == 20);
    }
}

TEST_CASE("Initialized Candies Vector Correctly") {
    Board board({100, 100}, {200, 200}, 5);
    SECTION("Correct Size") {
        REQUIRE(board.getCandies().size() == 5);
    }
    SECTION("No Three in a Rows") {
        bool three_in_a_row = false;
        for (size_t row = 0; row < board.getCandiesPerRow(); row++) {
            for (size_t col = 0; col < board.getCandiesPerRow(); col++) {
                std::string current_candy_color = board.getCandies()[row][col].getColor();
                if (row >= 2) {
                    std::string one_above_color = board.getCandies()[row-1][col].getColor();
                    std::string two_above_color = board.getCandies()[row-2][col].getColor();
                    if (current_candy_color == one_above_color && current_candy_color == two_above_color) {
                        three_in_a_row = true;
                    }
                }
                //makes sure there are no initial three in a rows horizontally
                if (col >= 2) {
                    std::string one_left_color = board.getCandies()[row][col-1].getColor();
                    std::string two_left_color = board.getCandies()[row][col-2].getColor();
                    if (current_candy_color == one_left_color && current_candy_color == two_left_color) {
                        three_in_a_row = true;
                    }
                }
            }
        }
        REQUIRE(three_in_a_row == false);
    }
}

TEST_CASE("Test Get Random Color method") {
    Board board({100, 100}, {200, 200}, 5);
    SECTION("Returns one of 4 colors") {
        std::string color = board.GetRandomColor();
        REQUIRE((color == "pink" || color == "teal" || color == "skyblue" || color == "purple"));
    }
}

TEST_CASE("Swap Candies Correctly") {
    Board board = CreateBoard();
    //pink pink skyblue
    //teal skyblue pink
    //teal skyblue purple
    SECTION("Test helper: Get Candies From Position") {
        glm::vec2 position = {110, 110};
        REQUIRE(board.GetCandyFromPosition(position).getColor() == "pink");
    }
    SECTION("Test helper: Get Candies From Position with non exact position") {
        glm::vec2 position = {108, 112};
        REQUIRE(board.GetCandyFromPosition(position).getColor() == "pink");
    }
    SECTION("Test swap given exact position") {
        glm::vec2 position1 = {110, 110};
        glm::vec2 position2 = {110, 130};
        board.SwapCandies(position1, position2);
        REQUIRE(board.GetCandyFromPosition(position1).getColor() == "teal");
        REQUIRE(board.GetCandyFromPosition(position2).getColor() == "pink");
    }
    SECTION("Test swap given non-exact position") {
        glm::vec2 position1 = {108, 112};
        glm::vec2 position2 = {111, 131};
        board.SwapCandies(position1, position2);
        REQUIRE(board.GetCandyFromPosition(position1).getColor() == "teal");
        REQUIRE(board.GetCandyFromPosition(position2).getColor() == "pink");
    }
    SECTION("Test invalid swap") {
        glm::vec2 position1 = {111, 109};
        glm::vec2 position2 = {148, 152};
        board.SwapCandies(position1, position2);
        REQUIRE(board.GetCandyFromPosition(position1).getColor() == "pink");
        REQUIRE(board.GetCandyFromPosition(position2).getColor() == "purple");
    }
    SECTION("Test invalid swap diagonal") {
        glm::vec2 position1 = {110, 110};
        glm::vec2 position2 = {130, 130};
        board.SwapCandies(position1, position2);
        REQUIRE(board.GetCandyFromPosition(position1).getColor() == "pink");
        REQUIRE(board.GetCandyFromPosition(position2).getColor() == "skyblue");
    }
}

TEST_CASE("Pop vertical") {
    Board board = CreateBoard();
    //pink pink skyblue
    //teal skyblue pink
    //teal skyblue purple
    SECTION("No three in a row") {
        REQUIRE(board.PopVertical() == false);
    }
    SECTION("There is a three in a row") {
        glm::vec2 position1 = {130, 110};
        glm::vec2 position2 = {150, 110};
        //create skyblue vertical three in a row
        board.SwapCandies(position1, position2);
        REQUIRE(board.PopVertical() == true);
    }
}

TEST_CASE("Pop Horizontal") {
    Board board = CreateBoard();
    //pink pink skyblue
    //teal skyblue pink
    //teal skyblue purple
    SECTION("No three in a row") {
        REQUIRE(board.PopHorizontal() == false);
    }
    SECTION("There is a three in a row") {
        glm::vec2 position1 = {150, 110};
        glm::vec2 position2 = {150, 130};
        //creates pink horizontal three in a row
        board.SwapCandies(position1, position2);
        REQUIRE(board.PopHorizontal() == true);
    }
}

TEST_CASE("Pop Candy") {
    Board board = CreateBoard();
    //pink pink skyblue
    //teal skyblue pink
    //teal skyblue purple
    SECTION("No three in a row") {
        REQUIRE(board.PopCandy() == false);
    }
    SECTION("There is a three in a row horizontally") {
        glm::vec2 position1 = {150, 110};
        glm::vec2 position2 = {150, 130};
        //creates pink horizontal three in a row
        board.SwapCandies(position1, position2);
        REQUIRE(board.PopCandy() == true);
    }
    SECTION("There is a three in a row vertically") {
        glm::vec2 position1 = {130, 110};
        glm::vec2 position2 = {150, 110};
        //create skyblue vertical three in a row
        board.SwapCandies(position1, position2);
        REQUIRE(board.PopCandy() == true);
    }
}

TEST_CASE("Drop Candies") {
    Board board = CreateBoard();
    //pink pink skyblue
    //teal skyblue pink
    //teal skyblue purple
    SECTION("Drop from row three") {
        board.DropCandies(2, 0);
        REQUIRE(board.getCandies()[2][0].getColor() == "teal");
        REQUIRE(board.getCandies()[1][0].getColor() == "pink");
    }
    SECTION("Drop from row two") {
        board.DropCandies(1, 1);
        REQUIRE(board.getCandies()[1][1].getColor() == "pink");
    }
    SECTION("Fills top column with random candy") {
        board.DropCandies(0, 2);
        std::string color = board.getCandies()[0][2].getColor();
        REQUIRE((color == "pink" || color == "teal" || color == "skyblue" || color == "purple"));
    }
}

TEST_CASE("Accurate points") {
    Board board3 = CreateBoard();
    //pink pink skyblue
    //teal skyblue pink
    //teal skyblue purple
    SECTION("starts with 0 points") {
        REQUIRE(board3.getCurrentPoints() == 0);
    }
    SECTION("Adds 3 points for a three in a row horizontally") {
        glm::vec2 position1 = {150, 110};
        glm::vec2 position2 = {150, 130};
        //creates pink horizontal three in a row
        board3.SwapCandies(position1, position2);
        board3.PopHorizontal();
        REQUIRE(board3.getCurrentPoints() == 3);
    }
    SECTION("Adds 3 points for a three in a row horizontally") {
        glm::vec2 position1 = {130, 110};
        glm::vec2 position2 = {150, 110};
        //create skyblue vertical three in a row
        board3.SwapCandies(position1, position2);
        board3.PopVertical();
        REQUIRE(board3.getCurrentPoints() == 3);
    }

    //4x4 board
    Board board4({100, 100}, {180, 180}, 4);
    std::vector<std::vector<Candy>> candies;
    std::vector<Candy> row1;
    row1.push_back(Candy("pink", {110, 110}));
    row1.push_back(Candy("pink", {130, 110}));
    row1.push_back(Candy("skyblue", {150, 110}));
    row1.push_back(Candy("pink", {170, 110}));
    candies.push_back(row1);
    std::vector<Candy> row2;
    row2.push_back(Candy("skyblue", {110, 130}));
    row2.push_back(Candy("purple", {130, 130}));
    row2.push_back(Candy("pink", {150, 130}));
    row2.push_back(Candy("teal", {170, 130}));
    candies.push_back(row2);
    std::vector<Candy> row3;
    row3.push_back(Candy("teal", {110, 150}));
    row3.push_back(Candy("skyblue", {130, 150}));
    row3.push_back(Candy("purple", {150, 150}));
    row3.push_back(Candy("pink", {170, 150}));
    candies.push_back(row3);
    std::vector<Candy> row4;
    row4.push_back(Candy("purple", {110, 170}));
    row4.push_back(Candy("teal", {130, 170}));
    row4.push_back(Candy("skyblue", {150, 170}));
    row4.push_back(Candy("pink", {170, 170}));
    candies.push_back(row4);
    board4.setCandies(candies);

    //pink pink skyblue pink
    //skyblue purple pink teal
    //teal skyblue purple pink
    //purple teal skyblue pink
    SECTION("Adds 4 points for a three in a row horizontally") {
        glm::vec2 position1 = {150, 110};
        glm::vec2 position2 = {150, 130};
        //creates pink horizontal three in a row
        board4.SwapCandies(position1, position2);
        board4.PopHorizontal();
        REQUIRE(board4.getCurrentPoints() == 4);
    }
    SECTION("Adds 4 points for a three in a row horizontally") {
        glm::vec2 position1 = {150, 130};
        glm::vec2 position2 = {170, 130};
        //create pink vertical three in a row
        board4.SwapCandies(position1, position2);
        board4.PopVertical();
        REQUIRE(board4.getCurrentPoints() == 4);
    }
}

