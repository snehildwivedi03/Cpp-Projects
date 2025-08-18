#include "Menu.h"
#include <iostream>
#include <algorithm>

Menu::Menu() {
    font.loadFromFile("assets/arial.ttf");

    title.setFont(font);
    title.setString("DSA Visualizer");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::Cyan);
    title.setPosition(100, 30);

    algorithms = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort"};
    selectedAlgoIndex = 0;
    numBars = 50;

    std::vector<std::string> items = {
        "Select Algorithm: " + algorithms[selectedAlgoIndex],
        "Number of Bars: " + std::to_string(numBars),
        "Start Visualization"
    };

    for (size_t i = 0; i < items.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(items[i]);
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::White);
        text.setPosition(100, 150 + static_cast<float>(i) * 60.f);
        menuItems.push_back(text);
    }

    selectedIndex = 0;
}

void Menu::handleInput(sf::Event event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedIndex = (selectedIndex - 1 + static_cast<int>(menuItems.size())) % static_cast<int>(menuItems.size());
        } else if (event.key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex + 1) % static_cast<int>(menuItems.size());
        } else if (event.key.code == sf::Keyboard::Left) {
            if (selectedIndex == 0) {
                selectedAlgoIndex = (selectedAlgoIndex - 1 + static_cast<int>(algorithms.size())) % static_cast<int>(algorithms.size());
                menuItems[0].setString("Select Algorithm: " + algorithms[selectedAlgoIndex]);
            } else if (selectedIndex == 1) {
                numBars = std::max(5, numBars - 5);
                menuItems[1].setString("Number of Bars: " + std::to_string(numBars));
            }
        } else if (event.key.code == sf::Keyboard::Right) {
            if (selectedIndex == 0) {
                selectedAlgoIndex = (selectedAlgoIndex + 1) % static_cast<int>(algorithms.size());
                menuItems[0].setString("Select Algorithm: " + algorithms[selectedAlgoIndex]);
            } else if (selectedIndex == 1) {
                numBars = std::min(400, numBars + 5);
                menuItems[1].setString("Number of Bars: " + std::to_string(numBars));
            }
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        for (size_t i = 0; i < menuItems.size(); i++) {
            if (menuItems[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                selectedIndex = static_cast<int>(i);
                // Click on Algorithm: cycle
                if (i == 0) {
                    selectedAlgoIndex = (selectedAlgoIndex + 1) % static_cast<int>(algorithms.size());
                    menuItems[0].setString("Select Algorithm: " + algorithms[selectedAlgoIndex]);
                }
                // Click on Bars: increment
                else if (i == 1) {
                    numBars = (numBars >= 400 ? 5 : numBars + 5);
                    menuItems[1].setString("Number of Bars: " + std::to_string(numBars));
                }
            }
        }
    }
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(title);
    for (size_t i = 0; i < menuItems.size(); i++) {
        menuItems[i].setFillColor(i == static_cast<size_t>(selectedIndex) ? sf::Color::Yellow : sf::Color::White);
        window.draw(menuItems[i]);
    }
}

std::string Menu::getSelectedAlgorithm() const {
    return algorithms[selectedAlgoIndex];
}

int Menu::getNumBars() const {
    return numBars;
}

bool Menu::isStartSelected() const {
    return selectedIndex == 2;
}
