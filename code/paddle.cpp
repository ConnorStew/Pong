#include "paddle.hpp"
#include "SFML/Graphics.hpp"

Paddle::Paddle(float x, float y, sf::Color colour) {
    this->x = x;
    this->y = y;
    this->speed = 0.5;

    shape = new sf::RectangleShape(sf::Vector2f(20,100));
    shape->setPosition(x,y);
    shape->setFillColor(colour);
}

void Paddle::move(Direction dir, float delta, float width, float height) {
    float moveSpeed = speed * delta;

    if (dir == UP) {
        float newY = y - moveSpeed;
        y = newY;
    }

    if (dir == DOWN) {
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