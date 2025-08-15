#pragma once
#include <SFML/Graphics.hpp>

class Visualizer {
public:
    virtual ~Visualizer() = default;

    // Called once per frame to update logic
    virtual void update(float dt) = 0;

    // Called once per frame to draw visuals
    virtual void draw(sf::RenderWindow& window) = 0;

    // Handle keyboard/mouse events
    virtual void handleEvent(const sf::Event& event) = 0;
};
