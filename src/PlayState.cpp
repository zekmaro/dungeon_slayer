#include "PlayState.hpp"
#include <iostream>

using T = TileType;

static const std::vector<std::vector<TileType>> MAP = {
    {T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Floor, T::Wall},
    {T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall,  T::Wall},
};

PlayState::PlayState(sf::Texture& playerTexture)
    : tilemap_(32),
      player_(playerTexture, {400.f, 300.f}) {
    tilemap_.load(MAP);
    enemies_.emplace_back(sf::Vector2f{100.f, 100.f});
}

void PlayState::handleEvent(const sf::Event& event) {}

void PlayState::update(float dt) {
    sf::Vector2f delta = player_.getMoveDelta(dt);
    delta.x = clampToWallX(delta.x);
    delta.y = clampToWallY(delta.y);
    player_.applyMove(delta);
    player_.tick(dt);

    for (auto& enemy : enemies_) {
        enemy.update(dt, player_.getPosition());
        if (player_.getBounds().findIntersection(enemy.getBounds()).has_value())
            player_.takeDamage();
    }

    if (player_.isDead())
        std::cout << "you died\n";
}

float PlayState::clampToWallX(float dx) {
    if (dx == 0.f) return 0.f;
    sf::FloatRect b = player_.getBounds();
    float ts = static_cast<float>(tilemap_.tileSize());
    int topRow = static_cast<int>((b.position.y + 1.f) / ts);
    int botRow = static_cast<int>((b.position.y + b.size.y - 2.f) / ts);

    if (dx < 0.f) {
        int col = static_cast<int>((b.position.x + dx) / ts);
        for (int row = topRow; row <= botRow; ++row)
            if (tilemap_.isWall(col, row))
                return (col + 1) * ts - b.position.x;
    } else {
        int col = static_cast<int>((b.position.x + b.size.x - 1.f + dx) / ts);
        for (int row = topRow; row <= botRow; ++row)
            if (tilemap_.isWall(col, row))
                return col * ts - (b.position.x + b.size.x);
    }
    return dx;
}

float PlayState::clampToWallY(float dy) {
    if (dy == 0.f) return 0.f;
    sf::FloatRect b = player_.getBounds();
    float ts = static_cast<float>(tilemap_.tileSize());
    int leftCol  = static_cast<int>((b.position.x + 1.f) / ts);
    int rightCol = static_cast<int>((b.position.x + b.size.x - 2.f) / ts);

    if (dy < 0.f) {
        int row = static_cast<int>((b.position.y + dy) / ts);
        for (int col = leftCol; col <= rightCol; ++col)
            if (tilemap_.isWall(col, row))
                return (row + 1) * ts - b.position.y;
    } else {
        int row = static_cast<int>((b.position.y + b.size.y - 1.f + dy) / ts);
        for (int col = leftCol; col <= rightCol; ++col)
            if (tilemap_.isWall(col, row))
                return row * ts - (b.position.y + b.size.y);
    }
    return dy;
}

void PlayState::draw(sf::RenderTarget& target) {
    tilemap_.draw(target);
    for (auto& enemy : enemies_)
        enemy.draw(target);
    player_.draw(target);
}
