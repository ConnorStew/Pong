#ifndef WORLD_H
#define WORLD_H

#include "SFML/Graphics.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "entity.hpp"

class World {
    public:
    World(sf::RenderWindow* win);
    bool canMove(Entity* entity, float newX, float newY);

    private:
    sf::RenderWindow* win;
    sf::Clock deltaClock;
    sf::RectangleShape* topWall;
    sf::RectangleShape* bottomWall;
    sf::RectangleShape* leftWall;
    sf::RectangleShape* rightWall;
    Paddle* pad1;
    Paddle* pad2;
    Ball* ball;

    void close();
    void update(double delta);
    void render();
    void checkCollisions();
    void paddleCheck(sf::FloatRect paddleRect, sf::FloatRect ballRect);
    float clip(float number, float lowest, float highest);
};
    
#endif