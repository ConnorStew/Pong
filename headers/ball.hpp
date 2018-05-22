#ifndef BALL_H
#define BALL_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "entity.hpp"
#include "direction.hpp"

class World;

class Ball : public Entity {
    public:
    Ball(World *world, float x, float y, sf::Color colour);
    void update(double delta);
    void bounce(Direction dir, float xModifier, float yModifier);

    private:
    float xDelta, yDelta;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    World *world;
};
    
#endif