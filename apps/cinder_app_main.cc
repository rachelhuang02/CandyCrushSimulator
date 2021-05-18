//
// Created by Rachel Huang on 4/16/21.
//

#include "candy_crush_simulation.h"

using candy_crush::CandyCrushGame;

void prepareSettings(CandyCrushGame::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(CandyCrushGame, ci::app::RendererGl, prepareSettings);
