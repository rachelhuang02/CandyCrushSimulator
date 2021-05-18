//
// Created by Rachel Huang on 4/28/21.
//

#include "game.h"

namespace candy_crush {

Game::Game(Board board, int goal_points, int time_per_game) {
 board_ = board;
 goal_points_ = goal_points;
 time_per_game_ = time_per_game;
}

void Game::DisplayGameInfo() {
    ci::gl::drawString("goal points: " + std::to_string((size_t) goal_points_),
                               {board_.getBottomRightCoordinate().x + 75, board_.getTopLeftCoordinate().y + 175},
            ci::Color("midnightblue"),
            ci::Font("Georgia", 30));

    ci::gl::drawString("wins: " + std::to_string((size_t) num_of_wins_),
                       {board_.getBottomRightCoordinate().x + 75,board_.getTopLeftCoordinate().y + 325},
                       ci::Color("midnightblue"),
                       ci::Font("georgia", 30));
}

void Game::DisplayLostGameScreen() {
    ci::gl::color(ci::Color("mistyrose"));
    ci::gl::drawSolidRect(ci::Rectf({0, 0}, {1000, 1000}));

    ci::gl::drawStringCentered("Sorry, you lost :(",{500, 250},
            ci::Color("midnightblue"),
            ci::Font("Arial", 50));

    if (num_of_wins_ == 1) {
        ci::gl::drawStringCentered("You have " + std::to_string(num_of_wins_) + " win!",{500, 315},
                                   ci::Color("midnightblue"),
                                   ci::Font("Arial", 30));
    } else {
        ci::gl::drawStringCentered("You have " + std::to_string(num_of_wins_) + " wins!",{500, 315},
                                   ci::Color("midnightblue"),
                                   ci::Font("Arial", 30));
    }

    ci::gl::drawStringCentered("Click anywhere to play again",{500, 400},
            ci::Color("midnightblue"),
            ci::Font("Arial", 25));
}

void Game::DisplayWonGameScreen() {
    ci::gl::color(ci::Color("honeydew"));
    ci::gl::drawSolidRect(ci::Rectf({0, 0}, {1000, 1000}));

    ci::gl::drawStringCentered("Yay! You won :)",{500, 250},
            ci::Color("lightcoral"),
            ci::Font("Arial", 50));

    if (num_of_wins_ == 1) {
        ci::gl::drawStringCentered("You have " + std::to_string(num_of_wins_) + " win!",{500, 315},
                                   ci::Color("lightcoral"),
                                   ci::Font("Arial", 30));
    } else {
        ci::gl::drawStringCentered("You have " + std::to_string(num_of_wins_) + " wins!",{500, 315},
                                   ci::Color("lightcoral"),
                                   ci::Font("Arial", 30));
    }

    ci::gl::drawStringCentered("Click anywhere to play again",{500, 400},
            ci::Color("lightcoral"),
            ci::Font("Arial", 25));
}

int Game::getGoalPoints() const {
    return goal_points_;
}

int Game::getTimePerGame() const {
    return time_per_game_;
}

int Game::getNumOfWins() const {
    return num_of_wins_;
}

void Game::setNumOfWins(int numOfWins) {
    num_of_wins_ = numOfWins;
}

}
