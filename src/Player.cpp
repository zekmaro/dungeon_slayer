#include "Player.hpp"

Player::Player(sf::Texture& texture, sf::Vector2f startPos)
    : sprite_(texture) {
    sprite_.setPosition(startPos);
}

sf::Vector2f Player::getMoveDelta(float dt) const {
    float speed = 300.f;
    sf::Vector2f delta;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) delta.y -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) delta.y += speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) delta.x -= speed * dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) delta.x += speed * dt;
    return delta;
}

void Player::applyMove(sf::Vector2f delta) {
    sprite_.move(delta);
}

void Player::tick(float dt) {
    if (damageCooldown_ > 0.f)
        damageCooldown_ -= dt;
}

void Player::draw(sf::RenderTarget& target) {
    target.draw(sprite_);
}

void Player::takeDamage() {
    if (damageCooldown_ <= 0.f) {
        health_--;
        damageCooldown_ = 1.f;
    }
}

void Player::setPosition(sf::Vector2f pos) {
    sprite_.setPosition(pos);
}

bool Player::isDead() const { return health_ <= 0; }
sf::FloatRect Player::getBounds() const { return sprite_.getGlobalBounds(); }
sf::Vector2f Player::getPosition() const { return sprite_.getPosition(); }
