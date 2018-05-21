#define __USE_MINGW_ANSI_STDIO 0

#include "entity.hpp"

Entity::Entity(float x, float y, float width, float height, sf::Color colour) {
    this->x = x;
    this->y = y;

    debugFont.loadFromFile("E:/Programs/C++_Workspace/SFMLPong/out/res/debug.ttf");
    debugText = sf::Text();
    debugText.setFont(debugFont);
    debugText.setCharacterSize(10);

    shape = new sf::RectangleShape(sf::Vector2f(width,height));
    shape->setPosition(x,y);
    shape->setFillColor(colour);
}

void Entity::drawDebug(sf::RenderWindow* win) {
    /*
    debugText.setFillColor(sf::Color::Blue);
    debugText.setPosition(shape->getPosition());
    debugText.setString(std::string(std::to_string(shape->getPosition().x)));
    win->draw(debugText);
    

    debugText.setFillColor(sf::Color::Red);
    debugText.setPosition(shape->getPosition());
    debugText.setString(std::string(std::to_string(shape->getPosition().y)));
    win->draw(debugText);
    */

    //height line
    sf::RectangleShape heightLine = sf::RectangleShape(sf::Vector2f(5,shape->getGlobalBounds().height));
    heightLine.setPosition(shape->getPosition());
    heightLine.setFillColor(sf::Color::Cyan);
    win->draw(heightLine);

    //height text
    debugText.setFillColor(sf::Color::Magenta);
    debugText.setString(std::string(std::to_string((int)(shape->getGlobalBounds().height))));
    debugText.setPosition(sf::Vector2f(shape->getPosition().x - this->debugText.getGlobalBounds().width - 10, (shape->getPosition().y + shape->getGlobalBounds().height / 2) - debugText.getCharacterSize() / 2));
    win->draw(debugText);
    
    //width line
    sf::RectangleShape widthLine = sf::RectangleShape(sf::Vector2f(shape->getGlobalBounds().width, 5));
    widthLine.setPosition(sf::Vector2f(shape->getPosition().x, shape->getPosition().y + shape->getGlobalBounds().height));
    widthLine.setFillColor(sf::Color::White);
    win->draw(widthLine);

    //width text
    debugText.setFillColor(sf::Color::Magenta);
    debugText.setString(std::string(std::to_string((int)(shape->getGlobalBounds().width))));
    debugText.setPosition(sf::Vector2f(shape->getPosition().x - (this->debugText.getGlobalBounds().width / 2) + 10, 20 + (shape->getPosition().y + shape->getGlobalBounds().height) - debugText.getCharacterSize() / 2));
    win->draw(debugText);
    
    //origin block
    sf::RectangleShape origin = sf::RectangleShape(sf::Vector2f(5,5));
    origin.setPosition(shape->getPosition());
    origin.setFillColor(sf::Color::Yellow);
    win->draw(origin);
}

sf::RectangleShape& Entity::getShape() {
    return *shape;
}