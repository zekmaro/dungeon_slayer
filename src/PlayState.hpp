#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Tilemap.hpp"

class PlayState : public GameState {
public:
    PlayState(sf::Texture& playerTexture);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target) override;

private:
    float clampToWallX(float dx);
    float clampToWallY(float dy);

    Tilemap tilemap_;
    Player player_;
    std::vector<Enemy> enemies_;
};
