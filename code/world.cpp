#include <bits/stdc++.h>
#include <iostream>
#include "world.hpp"
#include "utils.hpp"
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
            pad1->move(utils::UP, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pad1->move(utils::DOWN, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pad2->move(utils::UP, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pad2->move(utils::DOWN, delta, win->getSize().x, win->getSize().y);
        }

        checkCollisions();

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

void World::checkCollisions() {
    sf::RectangleShape circle = ball->getShape();
    sf::RectangleShape p1Rect = pad1->getShape();
    sf::RectangleShape p2Rect = pad2->getShape();
  
    if(p1Rect.getGlobalBounds().intersects(circle.getGlobalBounds())) {
        if (circle.getPosition().y > p1Rect.getGlobalBounds().top)
            ball->bounce(utils::UP);
        else
            ball->bounce(utils::RIGHT);
    }

    if(p2Rect.getGlobalBounds().intersects(circle.getGlobalBounds())) {
        ball->bounce(utils::LEFT);
    }

}

float World::clip(float number, float lowest, float highest) {
    return std::max(lowest, std::min(number, highest));
}