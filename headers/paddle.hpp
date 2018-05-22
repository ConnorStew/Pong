#ifndef PADDLE_H
#define PADDLE_H

class World;

class Paddle : public Entity {
    public:
    Paddle(World *world, float x, float y, float width, float height, sf::Color colour);
    void move(Direction dir, double delta);
    void update(double delta);

    private:
    float speed;
    World* world;
};
    
#endif