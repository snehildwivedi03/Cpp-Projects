#pragma once
#include "Visualizer.hpp"
#include <vector>

class SortingVisualizer : public Visualizer {
public:
    SortingVisualizer(unsigned int numBars, unsigned int windowWidth, unsigned int windowHeight);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;

private:
    std::vector<float> values;
    std::vector<sf::RectangleShape> bars;
    unsigned int winWidth, winHeight;

    // Bubble Sort tracking
    unsigned int i = 0, j = 0;
    bool sorting = true;
    float speed = 0.05f; // seconds per step
    float timer = 0.f;

    void swapBars(unsigned int a, unsigned int b);
    void resetBars();
};
