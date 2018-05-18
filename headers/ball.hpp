#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "direction.hpp"

class Ball {
    public:
    Ball(float x, float y, sf::Color colour);
    void update(float delta);
    sf::RectangleShape& getShape();
    void bounce(Direction dir, float xModifier, float yModifier);

    private:
    sf::RectangleShape* shape;
    float x, y, xDelta, yDelta;
};
    
#endif