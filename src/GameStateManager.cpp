#include "GameStateManager.hpp"

void GameStateManager::push(std::unique_ptr<GameState> state) {
    if (!states_.empty())
        states_.top()->onExit();
    states_.push(std::move(state));
    states_.top()->onEnter();
}

void GameStateManager::pop() {
    if (states_.empty()) return;
    states_.top()->onExit();
    states_.pop();
    if (!states_.empty())
        states_.top()->onEnter();
}

bool GameStateManager::isEmpty() const {
    return states_.empty();
}

void GameStateManager::handleEvent(const sf::Event& event) {
    if (!states_.empty())
        states_.top()->handleEvent(event);
}

void GameStateManager::update(float dt) {
    if (!states_.empty())
        states_.top()->update(dt);
}

void GameStateManager::draw(sf::RenderTarget& target) {
    if (!states_.empty())
        states_.top()->draw(target);
}
