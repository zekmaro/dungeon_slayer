#pragma once

#include <SFML/Graphics.hpp>

class Player {
private:
	sf::Sprite sprite;
	float damageCooldown;
	int health;

public:
    Player(sf::Vector2f startPos);

	void move(float dt);
    void takeDamage();
    bool isDead() const;
    sf::FloatRect getBounds() const;

};
