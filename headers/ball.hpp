#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Ball {
    public:
    Ball(float x, float y, sf::Color colour);
    void update(float delta);
    sf::CircleShape& getShape();
    void bounce();

    private:
    sf::CircleShape* shape;
    float x, y, xDelta, yDelta;
};
    
#endif