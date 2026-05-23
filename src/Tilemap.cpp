#include "Tilemap.hpp"

static const sf::Color COLOR_FLOOR = sf::Color(40,  40,  40);
static const sf::Color COLOR_WALL  = sf::Color(80,  80, 100);

Tilemap::Tilemap(unsigned int tileSize)
    : tileSize_(tileSize),
      vertices_(sf::PrimitiveType::Triangles) {}

void Tilemap::load(const std::vector<std::vector<TileType>>& grid) {
    vertices_.clear();

    for (unsigned int row = 0; row < grid.size(); ++row) {
        for (unsigned int col = 0; col < grid[row].size(); ++col) {
            sf::Color color = (grid[row][col] == TileType::Wall) ? COLOR_WALL : COLOR_FLOOR;
            addTile(col, row, color);
        }
    }
}

void Tilemap::draw(sf::RenderTarget& target) {
    target.draw(vertices_);
}

unsigned int Tilemap::tileSize() const { return tileSize_; }

void Tilemap::addTile(unsigned int col, unsigned int row, sf::Color color) {
    float x  = static_cast<float>(col * tileSize_);
    float y  = static_cast<float>(row * tileSize_);
    float ts = static_cast<float>(tileSize_);

    vertices_.append({{x,      y     }, color});
    vertices_.append({{x + ts, y     }, color});
    vertices_.append({{x + ts, y + ts}, color});

    vertices_.append({{x,      y     }, color});
    vertices_.append({{x + ts, y + ts}, color});
    vertices_.append({{x,      y + ts}, color});
}
