#include "../headers/world.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 500), "Pong");
    World world(&window, false);

    return 0;
}