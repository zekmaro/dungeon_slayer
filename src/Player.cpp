#include "Player.hpp"
#include <algorithm>

Player::Player(sf::Texture& texture, sf::Vector2f startPos)
    : sprite_(texture) {
    sprite_.setPosition(startPos);
}

void Player::move(float dt) {
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) sprite_.move({0, -speed * dt});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) sprite_.move({0,  speed * dt});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) sprite_.move({-speed * dt, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) sprite_.move({ speed * dt, 0});
}

void Player::update(float dt) {
    if (damageCooldown_ > 0.f)
        damageCooldown_ -= dt;
}

void Player::draw(sf::RenderTarget& target) {
    target.draw(sprite_);
}

void Player::checkBounds(sf::Vector2u windowSize) {
    sf::FloatRect bounds = sprite_.getGlobalBounds();
    sf::Vector2f pos = sprite_.getPosition();

    pos.x = std::max(0.f, std::min(pos.x, static_cast<float>(windowSize.x) - bounds.size.x));
    pos.y = std::max(0.f, std::min(pos.y, static_cast<float>(windowSize.y) - bounds.size.y));

    sprite_.setPosition(pos);
}

void Player::takeDamage() {
    if (damageCooldown_ <= 0.f) {
        health_--;
        damageCooldown_ = 1.f;
    }
}

bool Player::isDead() const { return health_ <= 0; }
sf::FloatRect Player::getBounds() const { return sprite_.getGlobalBounds(); }
sf::Vector2f Player::getPosition() const { return sprite_.getPosition(); }
