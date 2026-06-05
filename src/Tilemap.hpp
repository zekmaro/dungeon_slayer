#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class TileType { Floor, Wall };

class Tilemap {
public:
    Tilemap(unsigned int tileSize);

    void load(const std::vector<std::vector<TileType>>& grid);
    void draw(sf::RenderTarget& target);

    bool isWall(int col, int row) const;
    unsigned int tileSize() const;

private:
    void addTile(unsigned int col, unsigned int row, sf::Color color);

    unsigned int tileSize_;
    sf::VertexArray vertices_;
    std::vector<std::vector<TileType>> grid_;
};
