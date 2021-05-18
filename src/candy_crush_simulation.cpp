//
// Created by Rachel Huang on 4/18/21.
//

#include "candy_crush_simulation.h"

namespace candy_crush {

CandyCrushGame::CandyCrushGame() : board_({100, 100}, {600, 600}, 8),
                                   game_(board_, 50, 10), timer_(){
    ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void CandyCrushGame::draw() {
    ci::Color background_color("lemonchiffon");
    ci::gl::clear(background_color);

    board_.Display();
    game_.DisplayGameInfo();

    //draw time
    ci::gl::drawString("time left: " + std::to_string(
                                                (size_t) game_.getTimePerGame() - ((int) timer_.getSeconds())),
                               {board_.getBottomRightCoordinate().x + 75,
                                     board_.getTopLeftCoordinate().y + 250},
            ci::Color("midnightblue"),
            ci::Font("georgia", 30));

    //when the time runs out, reset points and update wins accordingly
    if (!timer_.isStopped() && (int) timer_.getSeconds() == game_.getTimePerGame()) {
        timer_.stop();
        if (board_.getCurrentPoints() > game_.getGoalPoints()) {
            game_.setNumOfWins( game_.getNumOfWins() + 1);
            board_.setCurrentPoints(0);
            last_result = 1;
        } else {
            board_.setCurrentPoints(0);
            last_result = 2;
        }
    }

    //displays the result screen when the timer is not going, or is not first time
    if (timer_.isStopped()) {
        if (last_result == 1) {
            game_.DisplayWonGameScreen();
        } else if (last_result == 2) {
            game_.DisplayLostGameScreen();
        }
    }
}

void CandyCrushGame::update() {
    AppBase::update();
}

void CandyCrushGame::mouseDown(ci::app::MouseEvent event) {
    position_vector_.push_back(event.getPos());
    if (position_vector_.size() == 2) {
        if (timer_.isStopped()) {
            timer_.start();
        }
        board_.SwapCandies(position_vector_[0], position_vector_[1]);
        while(board_.PopCandy()) {
        }
        position_vector_.clear();
    }
}

} //namespace candy crush