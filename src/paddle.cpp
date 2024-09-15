#include "../headers/paddle.hpp"
#include "../headers/entity.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Paddle::Paddle(float x, float y, float width, float height, sf::Color colour) : Entity::Entity(x, y, width, height, colour) {
    speed = 0.5;
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

void Paddle::update(float delta) {
    shape->setPosition(x,y);
}