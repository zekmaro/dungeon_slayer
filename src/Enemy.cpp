#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(sf::Vector2f pos, sf::Vector2f size)
    : shape_(size) {
    shape_.setPosition(pos);
    shape_.setFillColor(sf::Color::Red);
}

void Enemy::update(float dt, sf::Vector2f targetPos) {
    sf::Vector2f dir = targetPos - shape_.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len != 0.f)
        dir /= len;
    shape_.move(dir * speed_ * dt);
}

void Enemy::draw(sf::RenderTarget& target) {
    target.draw(shape_);
}

sf::FloatRect Enemy::getBounds() const { return shape_.getGlobalBounds(); }
sf::Vector2f Enemy::getPosition() const { return shape_.getPosition(); }
