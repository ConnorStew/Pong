#ifndef WORLD_H
#define WORLD_H

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
    void checkCollisions();
    float clip(float number, float lowest, float highest);
};
    
#endif