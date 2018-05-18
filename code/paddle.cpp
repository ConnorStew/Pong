#include "paddle.hpp"
#include "SFML/Graphics.hpp"

Paddle::Paddle(float x, float y, float width, float height, sf::Color colour) {
    this->x = x;
    this->y = y;
    this->speed = 0.5;

    shape = new sf::RectangleShape(sf::Vector2f(width, height));
    shape->setPosition(x,y);
    shape->setFillColor(colour);
}

void Paddle::move(Direction dir, float delta, float width, float height) {
    float moveSpeed = speed * delta;

    if (dir == Direction::UP) {
        float newY = y - moveSpeed;
        y = newY;
    }

    if (dir == Direction::DOWN) {
        float newY = y + moveSpeed;
        y = newY;
    }
}

void Paddle::update() {
    shape->setPosition(x,y);
}

sf::RectangleShape& Paddle::getShape() {
    return *shape;
}