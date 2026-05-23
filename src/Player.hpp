#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::Texture& texture, sf::Vector2f startPos);

    void move(float dt);
    void update(float dt);
    void draw(sf::RenderTarget& target);
    void checkBounds(sf::Vector2u windowSize);
    void takeDamage();

    bool isDead() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite_;
    int health_ = 3;
    float damageCooldown_ = 0.f;
};
