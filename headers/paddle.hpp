#ifndef PADDLE_H
#define PADDLE_H

#include "SFML/Graphics.hpp"
#include "entity.hpp"
#include "direction.hpp"

class Paddle : public Entity {
    public:
    Paddle(float x, float y, float width, float height, sf::Color colour);
    void move(Direction dir, float delta, float width, float height);
    void update(float delta);

    private:
    float speed;
};
    
#endif