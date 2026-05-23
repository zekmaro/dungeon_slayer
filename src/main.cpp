#include <SFML/Graphics.hpp>

void movePlayer(sf::RectangleShape& player, float dt) {
    float speed = 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player.move({0, -speed * dt});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player.move({0,  speed * dt});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player.move({-speed * dt, 0});
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player.move({ speed * dt, 0});
}

void moveEnemy(sf::RectangleShape& enemy, sf::RectangleShape& player, float dt) {
    sf::Vector2f enemyPos = enemy.getPosition();
    sf::Vector2f playerPos = player.getPosition();

    sf::Vector2f direction = playerPos - enemyPos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
        direction /= length;

    float speed = 100.f;
    enemy.move(direction * speed * dt);
}


void checkBounds(sf::RectangleShape& player, sf::RenderWindow& window) {
    sf::FloatRect bounds = player.getGlobalBounds();
    sf::Vector2u windowSize = window.getSize();

    sf::Vector2f pos = player.getPosition();

    // clamp both axes together
    pos.x = std::max(0.f, std::min(pos.x, (float)windowSize.x - bounds.size.x));
    pos.y = std::max(0.f, std::min(pos.y, (float)windowSize.y - bounds.size.y));

    player.setPosition(pos);
}

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "dungeon");

    sf::RectangleShape player(sf::Vector2f(32, 32));
    player.setPosition({400, 300});
    player.setFillColor(sf::Color::White);

    sf::RectangleShape enemy(sf::Vector2f(32, 32));
    enemy.setPosition({100, 100});
    enemy.setFillColor(sf::Color::Red);

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        movePlayer(player, dt);
        checkBounds(player, window);

        moveEnemy(enemy, player, dt);
        
        window.clear(sf::Color(20, 20, 20));

        window.draw(enemy);
        window.draw(player);

        window.display();
    }
}