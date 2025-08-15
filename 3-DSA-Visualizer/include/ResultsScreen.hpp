#ifndef RESULTS_SCREEN_HPP
#define RESULTS_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <string>

class ResultsScreen {
public:
    ResultsScreen();

    void setResults(const std::string& algorithm, int numBars, double timeMs);
    void handleInput(sf::Event event);
    void draw(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Text title;
    sf::Text algoText;
    sf::Text barsText;
    sf::Text timeText;
    sf::Text complexityText;
    sf::Text instruction;

    std::string getComplexity(const std::string& algorithm);
};

#endif
