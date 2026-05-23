#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(sf::Vector2f pos, sf::Vector2f size = {32.f, 32.f});

    void update(float dt, sf::Vector2f targetPos);
    void draw(sf::RenderTarget& target);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

private:
    sf::RectangleShape shape_;
    float speed_ = 100.f;
};
