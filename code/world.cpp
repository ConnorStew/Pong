#include "world.hpp"
#include <bits/stdc++.h>
#include "SFML/Graphics.hpp"

World::World(sf::RenderWindow* win) {
    this->win = win;
    this->deltaClock = new sf::Clock();
    this->pad1 = new Paddle(20,20,sf::Color::Green);
    this->pad2 = new Paddle(win->getSize().x-40,20,sf::Color::Red);
    this->ball = new Ball(100,100,sf::Color::Blue);

    render();
}

void World::render() {
    while (win->isOpen()) {
        

        //get time in microseconds then convert to milliseconds
        sf::Int32 deltaInt = deltaClock->restart().asMicroseconds();
        float delta = (float)deltaInt / 1000;

        pad1->update();
        pad2->update();
        ball->update(delta);

        sf::Event event;
        while (win->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win->close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pad1->move(Paddle::Direction::UP, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pad1->move(Paddle::Direction::DOWN, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pad2->move(Paddle::Direction::UP, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pad2->move(Paddle::Direction::DOWN, delta, win->getSize().x, win->getSize().y);
        }

        if (checkCollisions(ball->getShape(),pad2->getShape())) {
            ball->bounce();
        }

        //if (checkCollisions(ball->getShape(),pad1->getShape())) {
        //    ball->bounce();
        //}

        win->clear();
        win->draw(pad1->getShape());
        win->draw(pad2->getShape());
        win->draw(ball->getShape());
        win->display();
    }

    close();
}

void World::close() {
    delete this;
    
}

bool World::checkCollisions(sf::CircleShape circle, sf::RectangleShape rect) {
    sf::Vector2f circlePos = circle.getPosition();
    sf::Vector2f rectPos = rect.getPosition();
    float rectWidth = rect.getSize().x;
    float rectHeight = rect.getSize().y;
    float circleRadius = circle.getRadius();

    return circlePos.x + circleRadius * 2 > rectPos.x;
}

float World::clip(float number, float lowest, float highest) {
    return std::max(lowest, std::min(number, highest));
}