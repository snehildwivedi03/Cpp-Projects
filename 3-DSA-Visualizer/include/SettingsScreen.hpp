#ifndef SETTINGS_SCREEN_HPP
#define SETTINGS_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class SettingsScreen {
public:
    SettingsScreen();

    void handleInput(sf::Event event);
    void draw(sf::RenderWindow& window);

    int getNumBars() const { return numBars; }

private:
    sf::Font font;
    sf::Text title;
    sf::Text instruction;
    sf::Text numBarsText;

    int numBars;
};

#endif
