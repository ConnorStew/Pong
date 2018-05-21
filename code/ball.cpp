#include "ball.hpp"
#include "entity.hpp"
#include "SFML/Graphics.hpp"

static const float DRAG = 0.000005;

Ball::Ball(float x, float y, sf::Color colour) : Entity::Entity(x, y, 10, 10, colour) {
    this->xDelta = 0.7;
    this->yDelta = 0;
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

void Ball::bounce(Direction dir, float xModifier, float yModifier) {
    xDelta = xDelta + xModifier;
    yDelta = yDelta + yModifier;

    if (dir == Direction::LEFT || dir == Direction::RIGHT)
        xDelta = -xDelta;

    if (dir == Direction::UP || dir == Direction::DOWN)
        yDelta = -yDelta;
}