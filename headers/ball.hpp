#ifndef BALL_H
#define BALL_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "entity.hpp"
#include "direction.hpp"

class Ball : public Entity {
    public:
    Ball(float x, float y, sf::Color colour);
    void update(float delta);
    void bounce(Direction dir, float xModifier, float yModifier);

    private:
    float xDelta, yDelta;
    sf::SoundBuffer buffer;
    sf::Sound sound;
};
    
#endif