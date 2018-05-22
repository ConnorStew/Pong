#include "world.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 500), "Pong"); //sf::Style::Fullscreen
    World world(&window);

    return 0;
}