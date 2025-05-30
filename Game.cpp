#include "xAI.hpp"
#include <algorithm>

class Glyph : public Entity {
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    char type; // 'H', 'V', 'C'
    bool active;

public:
    Glyph(float x, float y, char t) : position(x, y), type(t), active(true) {
        shape.setSize(sf::Vector2f(40.f, 40.f));
        shape.setFillColor(t == 'H' ? sf::Color::Cyan : t == 'V' ? sf::Color::Magenta : sf::Color::Yellow);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void stabilize(float energy) override {} // Glyphs not stabilized
    char getType() const { return type; }
};

class Node : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    float energy;
    bool active;

public:
    Node(float x, float y) : position(x, y), energy(100.f), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {
        shape.setFillColor(energy > 0.f ? sf::Color::Red : sf::Color::Green);
    }
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active && energy > 0.f; }
    void stabilize(float e) override { energy -= e; if (energy < 0.f) energy = 0.f; }
};

class Source : public Entity {
private:
    sf::CircleShape shape;
    sf::Vector2f position;
    bool active;

public:
    Source(float x, float y) : position(x, y), active(true) {
        shape.setRadius(10.f);
        shape.setFillColor(sf::Color::Blue);
        shape.setPosition(position);
    }

    void update(float deltaTime) override {}
    void render(sf::RenderWindow& window) const override {
        if (active) window.draw(shape);
    }
    sf::Vector2f getPosition() const override { return position; }
    bool isActive() const override { return active; }
    void stabilize(float energy) override {} // Sources not stabilized
};

Game::Game(sf::RenderWindow& win) : window(win), cursorPos(0, 0), overload(0.f), rng(std::random_device{}()), isAllNodesStable(false) {
    grid.resize(5, std::vector<char>(5, ' '));
    nodes.push_back(std::make_unique<Node>(350.f, 250.f));
    nodes.push_back(std::make_unique<Node>(400.f, 300.f));
    sources.push_back(std::make_unique<Source>(250.f, 150.f));
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        } else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::R) {
                grid.assign(5, std::vector<char>(5, ' '));
                nodes.clear();
                sources.clear();
                nodes.push_back(std::make_unique<Node>(350.f, 250.f));
                nodes.push_back(std::make_unique<Node>(400.f, 300.f));
                sources.push_back(std::make_unique<Source>(250.f, 150.f));
                cursorPos = {0, 0};
                overload = 0.f;
                isAllNodesStable = false;
            } else if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            } else if (event.key.code == sf::Keyboard::Up && cursorPos.y > 0) {
                cursorPos.y--;
            } else if (event.key.code == sf::Keyboard::Down && cursorPos.y < 4) {
                cursorPos.y++;
            } else if (event.key.code == sf::Keyboard::Left && cursorPos.x > 0) {
                cursorPos.x--;
            } else if (event.key.code == sf::Keyboard::Right && cursorPos.x < 4) {
                cursorPos.x++;
            } else if (event.key.code == sf::Keyboard::Num1) {
                grid[cursorPos.y][cursorPos.x] = 'H';
            } else if (event.key.code == sf::Keyboard::Num2) {
                grid[cursorPos.y][cursorPos.x] = 'V';
            } else if (event.key.code == sf::Keyboard::Num3) {
                grid[cursorPos.y][cursorPos.x] = 'C';
            } else if (event.key.code == sf::Keyboard::Space) {
                // Trigger energy surge
                for (auto& node : nodes) {
                    if (node->isActive()) {
                        // Check if node is connected to source via glyphs
                        bool connected = false;
                        int sx = (sources[0]->getPosition().x - 250.f) / 50.f;
                        int sy = (sources[0]->getPosition().y - 150.f) / 50.f;
                        int nx = (node->getPosition().x - 250.f) / 50.f;
                        int ny = (node->getPosition().y - 150.f) / 50.f;
                        if (sx == nx && sy == ny) connected = true;
                        else {
                            // Simple path check (horizontal/vertical/cross connections)
                            if (grid[sy][sx] == 'H' && sx < nx && grid[sy][nx] == 'H') connected = true;
                            if (grid[sy][sx] == 'V' && sy < ny && grid[ny][sx] == 'V') connected = true;
                            if (grid[sy][sx] == 'C' && (sx == nx || sy == ny)) connected = true;
                        }
                        if (connected) {
                            node->stabilize(50.f);
                            overload += 10.f; // Surge increases overload
                        }
                    }
                }
            }
        }
    }
}

void Game::update(float deltaTime) {
    for (auto& node : nodes) {
        node->update(deltaTime);
        if (node->isActive()) {
            overload += 2.f * deltaTime; // Nodes increase overload over time
        }
    }
    for (auto& source : sources) {
        source->update(deltaTime);
    }
    if (overload > 100.f) overload = 100.f;
    isAllNodesStable = std::all_of(nodes.begin(), nodes.end(), [](const auto& node) { return !node->isActive(); });
}

void Game::render() {
    window.clear(sf::Color::Black);

    // Draw grid
    for (int i = 0; i <= 5; ++i) {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(250.f, 150.f + i * 50.f), sf::Color::White),
            sf::Vertex(sf::Vector2f(450.f, 150.f + i * 50.f), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
        line[0] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 150.f), sf::Color::White);
        line[1] = sf::Vertex(sf::Vector2f(250.f + i * 50.f, 350.f), sf::Color::White);
        window.draw(line, 2, sf::Lines);
    }

    // Draw glyphs
    for (int y = 0; y < 5; ++y) {
        for (int x = 0; x < 5; ++x) {
            if (grid[y][x] != ' ') {
                Glyph glyph(250.f + x * 50.f, 150.f + y * 50.f, grid[y][x]);
                glyph.render(window);
            }
        }
    }

    // Draw cursor
    sf::RectangleShape cursor(sf::Vector2f(50.f, 50.f));
    cursor.setFillColor(sf::Color::Transparent);
    cursor.setOutlineColor(sf::Color::Yellow);
    cursor.setOutlineThickness(2.f);
    cursor.setPosition(250.f + cursorPos.x * 50.f, 150.f + cursorPos.y * 50.f);
    window.draw(cursor);

    // Draw nodes and sources
    for (const auto& node : nodes) {
        node->render(window);
    }
    for (const auto& source : sources) {
        source->render(window);
    }

    // Draw overload meter
    sf::RectangleShape overloadBar(sf::Vector2f(200.f * (overload / 100.f), 20.f));
    overloadBar.setPosition(300.f, 50.f);
    overloadBar.setFillColor(overload > 80.f ? sf::Color::Red : sf::Color::Green);
    window.draw(overloadBar);

    // Draw win/lose condition
    if (isAllNodesStable) {
        sf::Text winText;
        winText.setString("Nodes Stabilized!");
        winText.setCharacterSize(24);
        winText.setFillColor(sf::Color::Green);
        winText.setPosition(300.f, 400.f);
        window.draw(winText);
    } else if (overload >= 100.f) {
        sf::Text loseText;
        loseText.setString("System Overloaded!");
        loseText.setCharacterSize(24);
        loseText.setFillColor(sf::Color::Red);
        loseText.setPosition(300.f, 400.f);
        window.draw(loseText);
    }

    window.display();
}
