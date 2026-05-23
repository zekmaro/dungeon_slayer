#include "PlayState.hpp"
#include <iostream>

PlayState::PlayState(sf::Texture& playerTexture, sf::Vector2u windowSize)
    : player_(playerTexture, {400.f, 300.f}),
      windowSize_(windowSize) {
    enemies_.emplace_back(sf::Vector2f{100.f, 100.f});
}

void PlayState::handleEvent(const sf::Event& event) {}

void PlayState::update(float dt) {
    player_.move(dt);
    player_.checkBounds(windowSize_);
    player_.update(dt);

    for (auto& enemy : enemies_) {
        enemy.update(dt, player_.getPosition());
        if (player_.getBounds().findIntersection(enemy.getBounds()).has_value())
            player_.takeDamage();
    }

    if (player_.isDead())
        std::cout << "you died\n";
}

void PlayState::draw(sf::RenderTarget& target) {
    for (auto& enemy : enemies_)
        enemy.draw(target);
    player_.draw(target);
}
