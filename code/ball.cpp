#include "ball.hpp"
#include "SFML/Graphics.hpp"

static const float DRAG = 0.0000005;

Ball::Ball(float x, float y, sf::Color colour) {
    this->x = x;
    this->y = y;
    this->xDelta = 0.09;
    this->yDelta = 0;

    shape = new sf::CircleShape(25);
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

sf::CircleShape& Ball::getShape() {
    return *shape;
}

void Ball::bounce() {
    xDelta = -xDelta;
}