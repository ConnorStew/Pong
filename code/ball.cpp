#include "ball.hpp"
#include "entity.hpp"
#include "SFML/Graphics.hpp"
#include "world.hpp"
#include <iostream>

const float MAX_Y_DELTA = 2;

Ball::Ball(World *world, float x, float y, sf::Color colour) : Entity::Entity(x, y, 10, 10, colour) {
    this->xDelta = 5;
    this->yDelta = 0;
    this->world = world;

    if (!buffer.loadFromFile("res/boop.wav")) {
        std::cout << "Failed to load sound file." << std::endl;
    }

    sound.setBuffer(buffer);
}

void Ball::update(double delta) {
    float newX = x + xDelta;
    float newY = y + yDelta;
    
    shape->setPosition(newX,newY);
    x = newX;
    y = newY;
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