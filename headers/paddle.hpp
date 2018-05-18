#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>
#include "direction.hpp"


class Paddle {
    public:
    Paddle(float x, float y, float width, float height, sf::Color colour);
    
    void move(Direction dir, float delta, float width, float height);
    void update();
    sf::RectangleShape& getShape();

    private:
    sf::RectangleShape* shape;
    float x, y, speed;
};
    
#endif