#pragma once
#include <SFML/Graphics.hpp>

class Visualizer {
public:
    virtual ~Visualizer() = default;
    virtual void update(float dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void handleEvent(const sf::Event& event) = 0;
};
