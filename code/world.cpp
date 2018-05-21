#include <bits/stdc++.h>
#include <iostream>
#include "world.hpp"
#include "direction.hpp"
#include "entity.hpp"
#include "SFML/Graphics.hpp"

World::World(sf::RenderWindow* win) {
    const float DISTANCE_FROM_WALLS = 80;
    const float DISTANCE_FROM_ROOF = 20;
    const float PADDLE_WIDTH = 20;
    const float PADDLE_HEIGHT = 100;
    const float WINDOW_WIDTH = win->getSize().x;
    const float WINDOW_HEIGHT = win->getSize().y;
    const float WALL_WIDTH = 10;

    this->win = win;
    this->deltaClock = new sf::Clock();

    this->pad1 = new Paddle(DISTANCE_FROM_WALLS, DISTANCE_FROM_ROOF, PADDLE_WIDTH, PADDLE_HEIGHT, sf::Color(250,20,20));
    this->pad2 = new Paddle(WINDOW_WIDTH - (DISTANCE_FROM_WALLS * 2), DISTANCE_FROM_WALLS, PADDLE_WIDTH, PADDLE_HEIGHT, sf::Color(250,20,20));
    this->ball = new Ball(100, 300, sf::Color::Blue);

    this->bottomWall = new sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WALL_WIDTH));
    bottomWall->setPosition(0, WINDOW_HEIGHT - bottomWall->getSize().y);
    bottomWall->setFillColor(sf::Color::Yellow);

    this->topWall = new sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WALL_WIDTH));
    topWall->setFillColor(sf::Color::Magenta);

    this->leftWall = new sf::RectangleShape(sf::Vector2f(WALL_WIDTH, WINDOW_HEIGHT - WALL_WIDTH * 2));
    leftWall->setFillColor(sf::Color::Cyan);
    leftWall->setPosition(0, WALL_WIDTH);

    this->rightWall = new sf::RectangleShape(sf::Vector2f(WALL_WIDTH, WINDOW_HEIGHT - WALL_WIDTH));
    rightWall->setPosition(WINDOW_WIDTH - rightWall->getSize().x, WALL_WIDTH);
    rightWall->setFillColor(sf::Color::Green);

    render();
}

void World::render() {
    while (win->isOpen()) {
        //get time in microseconds then convert to milliseconds
        sf::Int32 deltaInt = deltaClock->restart().asMicroseconds();
        float delta = (float)deltaInt / 1000;

        pad1->update(delta);
        pad2->update(delta);
        ball->update(delta);

        sf::Event event;
        while (win->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                win->close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            pad1->move(Direction::UP, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            pad1->move(Direction::DOWN, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            pad2->move(Direction::UP, delta, win->getSize().x, win->getSize().y);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            pad2->move(Direction::DOWN, delta, win->getSize().x, win->getSize().y);
        }

        checkCollisions();



        win->clear();
        win->draw(*topWall);
        win->draw(*bottomWall);
        win->draw(*leftWall);
        win->draw(*rightWall);
        win->draw(pad1->getShape());
        win->draw(pad2->getShape());
        win->draw(ball->getShape());
        //pad1->drawDebug(win);
        //pad2->drawDebug(win);
        //ball->drawDebug(win);
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
    sf::FloatRect bb = circle.getGlobalBounds();

    paddleCheck(p1Rect.getGlobalBounds(), bb);
    paddleCheck(p2Rect.getGlobalBounds(), bb);

    if (bb.intersects(bottomWall->getGlobalBounds()) || bb.intersects(topWall->getGlobalBounds())) {
        ball->bounce(Direction::UP, 0, 0);
    }

    if (bb.intersects(leftWall->getGlobalBounds()) || bb.intersects(rightWall->getGlobalBounds())) {
        ball->bounce(Direction::LEFT, 0, 0);
    }

}

void World::paddleCheck(sf::FloatRect paddleRect, sf::FloatRect ballRect) {
    if (paddleRect.intersects(ballRect)) {
        float centerY = paddleRect.top + paddleRect.height / 2;
        float distance = (ballRect.top + ballRect.height / 2) - centerY;

        //y distance from center of paddle
        ball->bounce(Direction::LEFT, 0, distance / 1000);
    }
}