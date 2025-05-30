#ifndef GAME_HPP
#define GAME_HPP
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <random>

class Game {
private:
    sf::RenderWindow& window;
    std::vector<std::vector<char>> grid; // 'H'=horizontal, 'V'=vertical, 'C'=cross, ' '=empty
    std::vector<std::unique_ptr<Entity>> nodes; // Unstable nodes
    std::vector<std::unique_ptr<Entity>> sources; // Energy sources
    sf::Vector2i cursorPos;
    float overload; // Overload level (0 to 100)
    std::mt19937 rng;
    bool isAllNodesStable;

public:
    Game(sf::RenderWindow& win);
    void handleEvents();
    void update(float deltaTime);
    void render();
};

#endif // GAME_HPP
