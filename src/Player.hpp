#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player(sf::Texture& texture, sf::Vector2f startPos);

    sf::Vector2f getMoveDelta(float dt) const;
    void applyMove(sf::Vector2f delta);
    void tick(float dt);
    void draw(sf::RenderTarget& target);
    void takeDamage();
    void setPosition(sf::Vector2f pos);

    bool isDead() const;
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite_;
    int health_ = 3;
    float damageCooldown_ = 0.f;
};
