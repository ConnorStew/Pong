#ifndef PADDLE_H
#define PADDLE_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Paddle {
    public:
    Paddle(float x, float y, sf::Color colour);
    enum Direction {UP, DOWN};
    void move(Direction dir, float delta, float width, float height);
    void update();
    sf::RectangleShape& getShape();

    private:
    sf::RectangleShape* shape;
    float x, y, speed;
};
    
#endif