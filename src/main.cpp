#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "GameStateManager.hpp"
#include "PlayState.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "dungeon master");

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/player.png")) {
        std::cout << "failed to load texture\n";
        return -1;
    }
    playerTexture.setSmooth(false);

    GameStateManager gsm;
    gsm.push(std::make_unique<PlayState>(playerTexture, window.getSize()));

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            gsm.handleEvent(*event);
        }

        float dt = clock.restart().asSeconds();
        gsm.update(dt);

        window.clear(sf::Color(20, 20, 20));
        gsm.draw(window);
        window.display();
    }
}
