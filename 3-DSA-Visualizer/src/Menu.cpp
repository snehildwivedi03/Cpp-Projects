#include "Menu.h"
#include <iostream>

Menu::Menu() {
    font.loadFromFile("assets/arial.ttf"); // make sure font exists

    // Title
    title.setFont(font);
    title.setString("DSA Visualizer");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::White);
    title.setPosition(200, 50);

    // Algorithms
    algorithms = {"Bubble Sort", "Insertion Sort", "Selection Sort"};
    selectedAlgoIndex = 0;
    numBars = 50;
    selectedIndex = 0;

    // Menu items
  sf::Text algoText("Algorithm: " + algorithms[selectedAlgoIndex], font, 24);
sf::Text barsText("Number of Bars: " + std::to_string(numBars), font, 24);
sf::Text startText("Start Visualization", font, 24);

}

void Menu::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            selectedIndex = (selectedIndex - 1 + menuItems.size()) % menuItems.size();
        } 
        else if (event.key.code == sf::Keyboard::Down) {
            selectedIndex = (selectedIndex + 1) % menuItems.size();
        } 
        else if (event.key.code == sf::Keyboard::Left) {
            if (selectedIndex == 0) { // change algo
                selectedAlgoIndex = (selectedAlgoIndex - 1 + algorithms.size()) % algorithms.size();
                menuItems[0].setString("Algorithm: " + algorithms[selectedAlgoIndex]);
            } else if (selectedIndex == 1 && numBars > 10) { // change bars
                numBars -= 10;
                menuItems[1].setString("Number of Bars: " + std::to_string(numBars));
            }
        } 
        else if (event.key.code == sf::Keyboard::Right) {
            if (selectedIndex == 0) {
                selectedAlgoIndex = (selectedAlgoIndex + 1) % algorithms.size();
                menuItems[0].setString("Algorithm: " + algorithms[selectedAlgoIndex]);
            } else if (selectedIndex == 1 && numBars < 200) {
                numBars += 10;
                menuItems[1].setString("Number of Bars: " + std::to_string(numBars));
            }
        }
    }

    // Highlight selection
    for (size_t i = 0; i < menuItems.size(); i++) {
        menuItems[i].setFillColor(i == selectedIndex ? sf::Color::Yellow : sf::Color::White);
    }
}

void Menu::draw(sf::RenderWindow &window) {
    window.draw(title);
    for (auto &item : menuItems) {
        window.draw(item);
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
