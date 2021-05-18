//
// Created by Rachel Huang on 4/17/21.
//

#ifndef FINAL_PROJECT_BOARD_H
#define FINAL_PROJECT_BOARD_H

#endif //FINAL_PROJECT_BOARD_H

#include "cinder/gl/gl.h"
#include "candy.h"

using glm::vec2;

namespace candy_crush {
class Board {
    private:
        int candies_per_row_;
        std::vector<std::vector<Candy>> candies_;
        glm::vec2 top_left_coordinate_;
        glm::vec2 bottom_right_coordinate_;
        int size_of_cell_;
        int current_points_;

        /**
         * Initializes the candies vector and makes sure that there are not three in a rows
         */
        void InitializeCandiesVector();

    public:
        /**
         * Default constructor
         */
        Board();

        /**
         * Board constructor that takes in corner coordinates and candies per row
         */
        Board(glm::vec2 top_left, glm::vec2 bottom_right, int candies_per_row);

        /**
         * Draws the board and calls draw candy
         */
        void Display();

        /**
         * Given the position, returns the appropriate candy
         */
        Candy GetCandyFromPosition(glm::vec2 &position);

        /**
         * Swaps the candies at the given positions
         */
        void SwapCandies(glm::vec2 &position1, glm::vec2 &position2);

        /**
         * Generates a random color for the candy
         */
        std::string GetRandomColor();

        /**
         * Shifts the candies above it down one space
         */
        void DropCandies(int row, int col);

        /**
         * If there is a three in a row vertically, pops them and drop the candies down
         */
        bool PopVertical();

        /**
         * If there is a three in a row horizontally, pops them and drop the candies down
         */
        bool PopHorizontal();

        /**
         * Returns true if there was a three in a row during this swap
         */
        bool PopCandy();

        /**getters and setters*/
        const std::vector<std::vector<Candy>> &getCandies() const;
        int getSizeOfCell() const;
        int getCandiesPerRow() const;
        const vec2 &getTopLeftCoordinate() const;
        const vec2 &getBottomRightCoordinate() const;
        int getCurrentPoints();
        void setCandies(std::vector<std::vector<Candy>> &candies);
        void setCurrentPoints(int currentPoints);
};
} //namespace candy_crush
