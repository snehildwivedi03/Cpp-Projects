#pragma once
#include <SFML/Graphics.hpp>

class SettingsScreen {
public:
    SettingsScreen();
    void handleInput(sf::Event event);
    void draw(sf::RenderWindow& window);
    int  getNumBars() const { return numBars; }

private:
    int numBars;
    sf::Font font;
    sf::Text title;
    sf::Text instruction;
    sf::Text numBarsText;
};
