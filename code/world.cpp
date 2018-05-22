#include <bits/stdc++.h>
#include <iostream>
#include "world.hpp"
#include "direction.hpp"
#include "paddle.hpp"
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
    this->deltaClock = sf::Clock();

    this->pad1 = new Paddle(this, DISTANCE_FROM_WALLS, DISTANCE_FROM_ROOF, PADDLE_WIDTH, PADDLE_HEIGHT, sf::Color::White);
    this->pad2 = new Paddle(this, WINDOW_WIDTH - DISTANCE_FROM_WALLS - PADDLE_WIDTH, DISTANCE_FROM_ROOF, PADDLE_WIDTH, PADDLE_HEIGHT, sf::Color::White);
    this->ball = new Ball(this, 120, 300, sf::Color::White);

    this->bottomWall = new sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WALL_WIDTH));
    bottomWall->setPosition(0, WINDOW_HEIGHT - bottomWall->getSize().y);
    bottomWall->setFillColor(sf::Color::White);

    this->topWall = new sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WALL_WIDTH));
    topWall->setFillColor(sf::Color::White);

    this->leftWall = new sf::RectangleShape(sf::Vector2f(WALL_WIDTH, WINDOW_HEIGHT - WALL_WIDTH * 2));
    leftWall->setFillColor(sf::Color::White);
    leftWall->setPosition(0, WALL_WIDTH);

    this->rightWall = new sf::RectangleShape(sf::Vector2f(WALL_WIDTH, WINDOW_HEIGHT - WALL_WIDTH * 2));
    rightWall->setPosition(WINDOW_WIDTH - rightWall->getSize().x, WALL_WIDTH);
    rightWall->setFillColor(sf::Color::White);


    //https://gamedev.stackexchange.com/questions/72630/should-game-logic-update-per-second-or-per-frame
    /*
    float updatesPerSec = 10;
    float skipTicks = updatesPerSec/1000;
    float nextUpdate = deltaClock.getElapsedTime().asSeconds();
    float currentTime = deltaClock.getElapsedTime().asSeconds();
    
    while (win->isOpen()) {
        currentTime = deltaClock.getElapsedTime().asSeconds();

        while (nextUpdate < currentTime) {
            update(skipTicks);
            nextUpdate += skipTicks;
        }

        float interpolation = (currentTime + skipTicks - nextUpdate) / skipTicks;
        std::cout << interpolation << std::endl;
        render(interpolation);
    }
    */

    
    //win->setVerticalSyncEnabled(true);

    //https://gafferongames.com/post/fix_your_timestep/
    //https://en.sfml-dev.org/forums/index.php?topic=21192.0
    const double deltaTime = 0.01; //the amount of time between game logic updates (in seconds) (10ms)
    double currentTime = deltaClock.getElapsedTime().asSeconds(); //get the current time 
    double accumulator = 0.0;

    while (win->isOpen()) {
        //the time since the program started
        double newTime = deltaClock.getElapsedTime().asSeconds();

        //the amount of time that has passed since relative to the last frame that was rendered
        double frameTime = newTime - currentTime;
        currentTime = newTime;

        //give the accumulator more time to do logic updates
        accumulator += frameTime;

        //update game logic until it has comsumed all time since the last frame
        while (accumulator >= deltaTime) {
            update(deltaTime);
            accumulator -= deltaTime;
        }
        render();

        // FPS - Shows in Console Window
        std::cout << "FPS: " << 1.0f / frameTime << std::endl;
    }
    

    close();
}

void World::update(double delta) {
    sf::Event event;
    while (win->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            win->close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        win->close();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        pad1->move(Direction::UP, delta);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        pad1->move(Direction::DOWN, delta);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        pad2->move(Direction::UP, delta);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        pad2->move(Direction::DOWN, delta);
    }    

    checkCollisions();

    pad1->update(delta);
    pad2->update(delta);
    ball->update(delta);
}

void World::render() {
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

void World::close() {
    delete this;
}

bool World::canMove(Entity* entity, float newX, float newY) {
    sf::FloatRect leftWallRect = leftWall->getGlobalBounds();
    sf::FloatRect rightWallRect = rightWall->getGlobalBounds();
    sf::FloatRect topWallRect = topWall->getGlobalBounds();
    sf::FloatRect bottomWallRect = bottomWall->getGlobalBounds();
    
    if (newX < leftWallRect.left + leftWallRect.width || //can't go lower than left wall
        newX > rightWallRect.left - rightWallRect.width || //can't go higher than right wall
        newY < topWallRect.top + topWallRect.height || //can't go higher than top wall
        newY + entity->getShape().getGlobalBounds().height > bottomWallRect.top //can't go lower than bottom wall
    ) {
        return false;
    } else {
        return true;
    }
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
        ball->bounce(Direction::LEFT, 0, distance / 100);
    }
}