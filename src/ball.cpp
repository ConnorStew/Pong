#include "../headers/ball.hpp"
#include "../headers/entity.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>

const float MAX_Y_DELTA = 1;

Ball::Ball(float x, float y, sf::Color colour) : Entity::Entity(x, y, 10, 10, colour) {
    this->xDelta = 0.45;
    this->yDelta = 0;

    if (!buffer.loadFromFile("res/boop.wav")) {
        std::cout << "Failed to load sound file." << std::endl;
    }

    sound.setBuffer(buffer);
}

void Ball::update(float delta) {
    y = y + (yDelta * delta);
    x = x + (xDelta * delta);

    shape->setPosition(x,y);
}

void Ball::bounce(Direction dir, float xModifier, float yModifier) {
    sound.play();

    xDelta = xDelta + xModifier;
    if ((yDelta + yModifier) < MAX_Y_DELTA)
        yDelta = yDelta + yModifier;

    if (dir == Direction::LEFT || dir == Direction::RIGHT)
        xDelta = -xDelta;

    if (dir == Direction::UP || dir == Direction::DOWN)
        yDelta = -yDelta;
}