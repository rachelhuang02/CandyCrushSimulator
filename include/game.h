//
// Created by Rachel Huang on 4/28/21.
//
#pragma once

#ifndef FINAL_PROJECT_GAME_H
#define FINAL_PROJECT_GAME_H

#endif //FINAL_PROJECT_GAME_H

#include "board.h"
#include "cinder/gl/gl.h"

using glm::vec2;

namespace candy_crush {
class Game {
private:
    Board board_;
    int goal_points_;
    int time_per_game_;
    int num_of_wins_ = 0;

public:
    int getTimePerGame() const;
    int getGoalPoints() const;

public:
    /**
     * Constructor
     */
    Game(Board board, int goal_points, int time_per_game);

    /**
     * Draws the goal points and the number of wins
     */
    void DisplayGameInfo();

    /**
     * The screen that appears when the player loses
     */
    void DisplayLostGameScreen();

    /**
     * The screen that appears when the player wins
     */
    void DisplayWonGameScreen();

    /**Getters and Setters*/
    int getNumOfWins() const;
    void setNumOfWins(int numOfWins);

};

} //namespace