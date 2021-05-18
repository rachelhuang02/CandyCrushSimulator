//
// Created by Rachel Huang on 4/17/21.
//
#pragma once

#ifndef FINAL_PROJECT_CANDY_H
#define FINAL_PROJECT_CANDY_H

#endif //FINAL_PROJECT_CANDY_H

#include "cinder/gl/gl.h"

using glm::vec2;

namespace candy_crush {
class Candy {
    private:
        std::string color_;
        std::string shape_;
        int size_;
        glm::vec2 position_;

public:
        /**
         * Default constructor
         */
        Candy();

        /**
         * Constructor that takes in color and position of candy
         */
        Candy(std::string color, glm::vec2 position);

        /**
         * Draws the candy
         */
        void DrawCandy();

        /**Getters and Setters*/
        const std::string &getColor() const;
        void setColor(const std::string &color);
        const std::string &getShape() const;
        void setShape(const std::string &shape);
        int getSize() const;
        void setSize(int size);
        const vec2 &getPosition() const;
        void setPosition(const vec2 &position);
};
} //namespace candy_crush

