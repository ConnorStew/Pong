#include "world.hpp"
#include "paddle.hpp"
#include "SFML/Graphics/font.hpp"
#include "SFML/Graphics.hpp"
#include "entity.hpp"
#include <cmath>
#include <iostream>

Paddle::Paddle(World* world,float x, float y, float width, float height, sf::Color colour) : Entity::Entity(x, y, width, height, colour) {
    speed = 5;
    this->world = world;
}

void Paddle::move(Direction dir, double delta) {
    float moveSpeed = speed;
    float newY = y;
    float newX = x;

    if (dir == Direction::UP) {
        newY -= moveSpeed;
    }

    if (dir == Direction::DOWN) {
        newY += moveSpeed;
    }

    if (world->canMove(this, newX, newY)) {
        x = newX;
        y = newY;
    }
}

void Paddle::update(double delta) {
    shape->setPosition(x,y);
}