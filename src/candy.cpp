//
// Created by Rachel Huang on 4/17/21.
//

#include "candy.h"

namespace candy_crush {

Candy::Candy(std::string color, glm::vec2 position) {
    color_ = color;
    position_ = position;
    if (color_ == "pink") {
        shape_ = "circle";
    } else if (color_ == "teal") {
        shape_ = "triangle";
    } else if (color_ == "skyblue") {
        shape_ = "ellipse";
    } else {
        shape_ = "square";
    }
    size_ = 20;
}

void Candy::DrawCandy() {
    ci::gl::color(ci::Color(color_.c_str()));
    if (color_ == "pink") {
        ci::gl::drawSolidCircle(position_, size_, -1);
    } else if (color_ == "teal") {
        ci::gl::drawSolidTriangle(glm::vec2(position_.x, position_.y - size_),
                                  glm::vec2(position_.x + size_, position_.y + size_),
                                  glm::vec2(position_.x - size_, position_.y + size_));
    } else if (color_ == "skyblue") {
        ci::gl::drawSolidEllipse(position_, size_ - 5, size_, -1);
    } else {
        ci::gl::drawSolidRect(ci::Rectf(glm::vec2(position_.x - size_, position_.y - size_),
                              glm::vec2(position_.x + size_, position_.y + size_)));
    }
}

const std::string &Candy::getColor() const {
    return color_;
}

void Candy::setColor(const std::string &color) {
    color_ = color;
}

const std::string &Candy::getShape() const {
    return shape_;
}

void Candy::setShape(const std::string &shape) {
    shape_ = shape;
}

int Candy::getSize() const {
    return size_;
}

void Candy::setSize(int size) {
    size_ = size;
}

const vec2 &Candy::getPosition() const {
    return position_;
}

void Candy::setPosition(const vec2 &position) {
    position_ = position;
}

Candy::Candy() {

}

}

