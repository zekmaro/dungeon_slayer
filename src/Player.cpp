#include "Player.hpp"

Player::Player(sf::Vector2f startPos) : shape({32, 32}), damageCooldown(0), health(3) {
	shape.setPosition(startPos);
	shape.setFillColor(sf::Color::White);
}

