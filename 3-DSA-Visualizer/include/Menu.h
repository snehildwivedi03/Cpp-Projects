#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    sf::Font font;
    sf::Text title;
    std::vector<sf::Text> menuItems;
    int selectedIndex;

    std::vector<std::string> algorithms;
    int selectedAlgoIndex;
    int numBars;

public:
    Menu();
    void handleInput(sf::Event event, sf::RenderWindow& window);
    void draw(sf::RenderWindow &window);

    std::string getSelectedAlgorithm() const;
    int getNumBars() const;
    bool isStartSelected() const;
};

#endif
