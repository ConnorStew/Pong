#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
    public:
    Entity(float x, float y, float width, float height, sf::Color colour);
    sf::RectangleShape& getShape();
    void update(float delta);
    void drawDebug(sf::RenderWindow* win);
    
    protected:
    float x, y, speed;
    sf::RectangleShape* shape;
    sf::Text debugText;
    sf::Font debugFont;
};
    
#endif