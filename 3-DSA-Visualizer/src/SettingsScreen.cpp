#include "SettingsScreen.hpp"
#include <iostream>

SettingsScreen::SettingsScreen() {
    numBars = 50;

    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Error loading font in SettingsScreen\n";
    }

    title.setFont(font);
    title.setString("Settings");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 50);

    instruction.setFont(font);
    instruction.setString("Use UP/DOWN to change number of bars.\nPress ENTER to start sorting.");
    instruction.setCharacterSize(20);
    instruction.setFillColor(sf::Color(200, 200, 200));
    instruction.setPosition(100, 120);

    numBarsText.setFont(font);
    numBarsText.setCharacterSize(30);
    numBarsText.setFillColor(sf::Color::Yellow);
    numBarsText.setPosition(100, 200);
    numBarsText.setString("Number of Bars: " + std::to_string(numBars));
}

void SettingsScreen::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            numBars += 5;
            if (numBars > 200) numBars = 200;
        }
        if (event.key.code == sf::Keyboard::Down) {
            numBars -= 5;
            if (numBars < 5) numBars = 5;
        }
        numBarsText.setString("Number of Bars: " + std::to_string(numBars));
    }
}

void SettingsScreen::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(instruction);
    window.draw(numBarsText);
}
