//
// Created by Rachel Huang on 4/17/21.
//
#include "board.h"

namespace candy_crush {

Board::Board() {
}

Board::Board(glm::vec2 top_left, glm::vec2 bottom_right, int candies_per_row) {
    top_left_coordinate_ = top_left;
    bottom_right_coordinate_ = bottom_right;
    candies_per_row_ = candies_per_row;
    size_of_cell_ = (bottom_right_coordinate_.x - top_left_coordinate_.x) / candies_per_row;
    InitializeCandiesVector();
    current_points_ = 0;
}

void Board::InitializeCandiesVector() {
    for (size_t row = 0; row < candies_per_row_; row++) {
        std::vector<Candy> row_of_candies;
        for (size_t col = 0; col < candies_per_row_; col++) {
            glm::vec2 position = glm::vec2(top_left_coordinate_.x + col * size_of_cell_ + size_of_cell_/2,
                                           top_left_coordinate_.y + row * size_of_cell_ + size_of_cell_/2);
            std::string color = GetRandomColor();
            //makes sure there are no initial three in a rows vertically
            if (row >= 2) {
                std::string one_above_color = candies_[row-1][col].getColor();
                std::string two_above_color = candies_[row-2][col].getColor();
                while (color == one_above_color && color == two_above_color) {
                    color = GetRandomColor();
                }
            }
            //makes sure there are no initial three in a rows horizontally
            if (col >= 2) {
                std::string one_left_color = row_of_candies[col-1].getColor();
                std::string two_left_color = row_of_candies[col-2].getColor();
                while (color == one_left_color && color == two_left_color) {
                    color = GetRandomColor();
                }
            }
            Candy candy(color, position);
            row_of_candies.push_back(candy);
        }
        candies_.push_back(row_of_candies);
    }
}

void Board::Display() {
    ci::gl::color(ci::Color("midnightblue"));
    ci::gl::drawStrokedRect(ci::Rectf(vec2(top_left_coordinate_.x, top_left_coordinate_.y),
                                      vec2(bottom_right_coordinate_.x, bottom_right_coordinate_.y)));
    //draw grid
    int x_value = top_left_coordinate_.x;
    int y_value = top_left_coordinate_.y;
    for (size_t i = 0; i < candies_per_row_; i++) {
        ci::gl::drawLine({x_value, top_left_coordinate_.y},{x_value, bottom_right_coordinate_.y});
        ci::gl::drawLine({top_left_coordinate_.x, y_value},{bottom_right_coordinate_.x, y_value});
        x_value += size_of_cell_;
        y_value += size_of_cell_;
    }
    //draw candy
    for (size_t row = 0; row < candies_per_row_; row++) {
        for (size_t col = 0; col < candies_per_row_; col++) {
            candies_[row][col].DrawCandy();
        }
    }

    ci::gl::drawString("current points: " + std::to_string((size_t) current_points_),
                               {bottom_right_coordinate_.x + 75, top_left_coordinate_.y + 100},
                                ci::Color("midnightblue"),
                                ci::Font("Georgia", 30));
}

std::string Board::GetRandomColor() {
    int random_int = rand()%(4) + 1;
    std::string color = "";
    switch(random_int) {
        case 1:
            color = "pink";
            break;
        case 2:
            color = "teal";
            break;
        case 3:
            color = "skyblue";
            break;
        case 4:
            color = "purple";
            break;
    }
    return color;
}

Candy Board::GetCandyFromPosition(glm::vec2 &position) {
    Candy candy_to_return;
    for (size_t row = 0; row < candies_per_row_; row++) {
        for (size_t col = 0; col < candies_per_row_; col++) {
            if (abs(candies_[row][col].getPosition().x - position.x) <= size_of_cell_/2 &&
                abs(candies_[row][col].getPosition().y - position.y) <= size_of_cell_/2) {
                candy_to_return = candies_[row][col];
            }
        }
    }
    return candy_to_return;
}

void Board::SwapCandies(glm::vec2 &position1, glm::vec2 &position2) {
    //makes sure that you can only switch positions with an adjacent candy
    if ((abs(GetCandyFromPosition(position1).getPosition().x -
            GetCandyFromPosition(position2).getPosition().x) +
        abs(GetCandyFromPosition(position1).getPosition().y -
            GetCandyFromPosition(position2).getPosition().y)) > size_of_cell_) {
        return;
    }
    Candy candy1 = GetCandyFromPosition(position1);
    Candy candy2 = GetCandyFromPosition(position2);
    for (size_t row = 0; row < candies_per_row_; row++) {
        for (size_t col = 0; col < candies_per_row_; col++) {
            if (abs(candies_[row][col].getPosition().x - position1.x) <= size_of_cell_/2 &&
                abs(candies_[row][col].getPosition().y - position1.y) <= size_of_cell_/2) {
                //swap index in array and swap position field
                candies_[row][col] = candy2;
                candies_[row][col].setPosition(candy1.getPosition());
            }
            if (abs(candies_[row][col].getPosition().x - position2.x) <= size_of_cell_/2 &&
                abs(candies_[row][col].getPosition().y - position2.y) <= size_of_cell_/2) {
                //swap index in array and swap position field
                candies_[row][col] = candy1;
                candies_[row][col].setPosition(candy2.getPosition());
            }
        }
    }
}

bool Board::PopVertical() {
    int amount_to_drop;
    //loops through each candy, checks for a three, four, or five in a row, and pops the appropriate candies
    for (size_t col = 0; col < candies_per_row_; col++) {
        for (size_t row = 0; row < candies_per_row_ - 2; row++) {
            std::string current_color = candies_[row][col].getColor();
            if (current_color == candies_[row+1][col].getColor() &&
                current_color == candies_[row+2][col].getColor()) {
                amount_to_drop = 3;
                //checks for 4 in a row
                if (row < (candies_per_row_ - 3) && current_color == candies_[row+3][col].getColor()) {
                    amount_to_drop = 4;
                    //checks for 5 in a row
                    if ((row < candies_per_row_ - 4) && current_color == candies_[row+4][col].getColor()) {
                        amount_to_drop = 5;
                    }
                }
                for (int i = 0; i < amount_to_drop; i++) {
                    DropCandies(row + i, col);
                }
                current_points_ += amount_to_drop;
                return true;
            }
        }
    }
    return false;
}

bool Board::PopHorizontal() {
    int amount_to_drop;
    //loops through each candy, checks for a three, four, or five in a row, and pops the appropriate candies
    for (size_t row = 0; row < candies_per_row_; row++) {
        for (size_t col = 0; col < candies_per_row_ - 2; col++) {
            std::string current_color = candies_[row][col].getColor();
            if (current_color == candies_[row][col+1].getColor() &&
                current_color == candies_[row][col+2].getColor()) {
                amount_to_drop = 3;
                //checks for 4 in a row
                if (col < (candies_per_row_ - 3) && current_color == candies_[row][col+3].getColor()) {
                    amount_to_drop = 4;
                    //checks for 5 in a row
                    if ((col < candies_per_row_ - 4) && current_color == candies_[row][col+4].getColor()) {
                        amount_to_drop = 5;
                    }
                }
                for (size_t i = 0; i < amount_to_drop; i++) {
                    DropCandies(row, col + i);
                }
                current_points_ += amount_to_drop;
                return true;
            }
        }
    }
    return false;
}

bool Board::PopCandy() {
    if (PopHorizontal()) {
        return true;
    }
    if (PopVertical()) {
        return true;
    }
    return false;
}

void Board::DropCandies(int row, int col) {
    int current_row = row;
    while (current_row >= 0) {
        glm::vec2 current_position = candies_[current_row][col].getPosition();
        //puts a random candy at the top of the column
        if (current_row == 0) {
            std::string color = GetRandomColor();
            Candy candy(color, current_position);
            candies_[current_row][col] = candy;
            break;
        // moves all the candies in a column down one spot
        } else {
            candies_[current_row][col] = candies_[current_row-1][col];
            candies_[current_row][col].setPosition(current_position);
            current_row--;
        }
    }
}

const std::vector<std::vector<Candy>> &Board::getCandies() const {
    return candies_;
}

int Board::getSizeOfCell() const {
    return size_of_cell_;
}

int Board::getCandiesPerRow() const {
    return candies_per_row_;
}

const vec2 &Board::getTopLeftCoordinate() const {
    return top_left_coordinate_;
}

const vec2 &Board::getBottomRightCoordinate() const {
    return bottom_right_coordinate_;
}

void Board::setCandies(std::vector<std::vector<Candy>> &candies) {
    candies_ = candies;
}

int Board::getCurrentPoints() {
    return current_points_;
}

void Board::setCurrentPoints(int currentPoints) {
    current_points_ = currentPoints;
}

} //namespace candy_crush