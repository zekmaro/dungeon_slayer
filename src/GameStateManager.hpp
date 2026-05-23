#pragma once
#include <stack>
#include <memory>
#include "GameState.hpp"

class GameStateManager {
public:
    void push(std::unique_ptr<GameState> state);
    void pop();
    bool isEmpty() const;

    void handleEvent(const sf::Event& event);
    void update(float dt);
    void draw(sf::RenderTarget& target);

private:
    std::stack<std::unique_ptr<GameState>> states_;
};
