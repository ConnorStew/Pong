#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "paddle.hpp"

class World {
    public:
    World(sf::RenderWindow* win);
    void render();

    private:
    sf::RenderWindow* win;
    sf::Clock* deltaClock;
    Paddle* pad1;
    Paddle* pad2;
    Ball* ball;

    void close();
    bool checkCollisions(sf::CircleShape circle, sf::RectangleShape rect);
    float clip(float number, float lowest, float highest);
};
    
#endif