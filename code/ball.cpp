#include "ball.hpp"
#include "world.hpp"
#include "SFML/Graphics.hpp"

static const float DRAG = 0.0000005;

Ball::Ball(float x, float y, sf::Color colour) {
    this->x = x;
    this->y = y;
    this->xDelta = 0.7;
    this->yDelta = 0;

    shape = new sf::RectangleShape(sf::Vector2f(10,10));
    shape->setPosition(x,y);
    shape->setFillColor(colour);
}

void Ball::update(float delta) {
    if (yDelta > 0)
        yDelta -= DRAG;
    
    if (yDelta < 0)
        yDelta += DRAG;

    if (xDelta > 0)
        xDelta -= DRAG;

    if (xDelta < 0)
        xDelta += DRAG;

    y = y + (yDelta * delta);
    x = x + (xDelta * delta);

    shape->setPosition(x,y);
}

sf::RectangleShape& Ball::getShape() {
    return *shape;
}

void Ball::bounce(utils::Direction dir, float xModifier, float yModifier) {
    xDelta = xDelta + xModifier;
    yDelta = yDelta + yModifier;

    if (dir == utils::Direction::LEFT || dir == utils::Direction::RIGHT)
        xDelta = -xDelta;

    if (dir == utils::Direction::UP || dir == utils::Direction::DOWN)
        yDelta = -yDelta;
}