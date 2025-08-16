#include "SortingVisualizer.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>

SortingVisualizer::SortingVisualizer(unsigned int numBars,
                                     unsigned int windowWidth,
                                     unsigned int windowHeight,
                                     const std::string& selectedAlgorithm)
    : winWidth(windowWidth), winHeight(windowHeight), algorithm(selectedAlgorithm)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    values.resize(numBars);
    bars.resize(numBars);
    resetBars();
}

void SortingVisualizer::resetBars() {
    i = j = 0;
    sorting = true;

    unsigned int numBars = values.size();
    float barWidth = static_cast<float>(winWidth) / numBars;

    // Generate random heights and create bars
    for (unsigned int k = 0; k < numBars; k++) {
        values[k] = static_cast<float>(std::rand() % (winHeight - 50) + 10); // avoid 0 height

        bars[k].setSize(sf::Vector2f(barWidth - 1, values[k]));
        bars[k].setPosition(k * barWidth, winHeight - values[k]);
        bars[k].setFillColor(sf::Color::Green);
    }
}

void SortingVisualizer::swapBars(unsigned int a, unsigned int b) {
    std::swap(values[a], values[b]);

    bars[a].setSize(sf::Vector2f(bars[a].getSize().x, values[a]));
    bars[a].setPosition(bars[a].getPosition().x, winHeight - values[a]);

    bars[b].setSize(sf::Vector2f(bars[b].getSize().x, values[b]));
    bars[b].setPosition(bars[b].getPosition().x, winHeight - values[b]);
}

void SortingVisualizer::update(float dt) {
    if (!sorting) return;

    timer += dt;
    if (timer >= speed) {
        timer = 0.f;

        if (i < values.size()) {
            if (j < values.size() - i - 1) {
                // Highlight bars being compared
                bars[j].setFillColor(sf::Color::Red);
                bars[j+1].setFillColor(sf::Color::Red);

                if (values[j] > values[j+1]) {
                    swapBars(j, j+1);
                }

                // Reset colors
                bars[j].setFillColor(sf::Color::Green);
                bars[j+1].setFillColor(sf::Color::Green);

                j++;
            } else {
                j = 0;
                i++;
            }
        } else {
            sorting = false;
        }
    }
}

void SortingVisualizer::draw(sf::RenderWindow& window) {
    for (auto& bar : bars) {
        window.draw(bar);
    }
}

void SortingVisualizer::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::R) {
            resetBars();
        }
        if (event.key.code == sf::Keyboard::Up) {
            speed = std::max(0.01f, speed - 0.01f);
        }
        if (event.key.code == sf::Keyboard::Down) {
            speed += 0.01f;
        }
    }
}
