//
// Created by Rachel Huang on 4/18/21.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Timer.h"
#include "game.h"


using glm::vec2;

#ifndef FINAL_PROJECT_CANDY_CRUSH_GAME_H
#define FINAL_PROJECT_CANDY_CRUSH_GAME_H

#endif //FINAL_PROJECT_CANDY_CRUSH_GAME_H

namespace candy_crush {
class CandyCrushGame : public ci::app::App {
public:
    CandyCrushGame();

    /**
     * Draws timer, candies, and game info
     */
    void draw() override;

    /**
     * Updates the app as needed
     */
    void update() override;

    /**
     * Swaps and pops candies after two candies are clicked and starts timer
     */
    void mouseDown(ci::app::MouseEvent event) override;

    const int kWindowSize = 1000;

private:
    Board board_;
    std::vector<glm::vec2> position_vector_;
    Game game_;
    cinder::Timer timer_;
    int last_result = 0;
};

} //namespace candycrush
