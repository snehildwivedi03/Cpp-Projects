#include "ResultsScreen.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

ResultsScreen::ResultsScreen() {
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Error loading font in ResultsScreen\n";
    }

    title.setFont(font);
    title.setString("Results");
    title.setCharacterSize(40);
    title.setFillColor(sf::Color::White);
    title.setPosition(100, 50);

    algoText.setFont(font);
    algoText.setCharacterSize(25);
    algoText.setFillColor(sf::Color::Yellow);
    algoText.setPosition(100, 120);

    barsText.setFont(font);
    barsText.setCharacterSize(25);
    barsText.setFillColor(sf::Color::Yellow);
    barsText.setPosition(100, 160);

    timeText.setFont(font);
    timeText.setCharacterSize(25);
    timeText.setFillColor(sf::Color::Yellow);
    timeText.setPosition(100, 200);

    complexityText.setFont(font);
    complexityText.setCharacterSize(25);
    complexityText.setFillColor(sf::Color::Cyan);
    complexityText.setPosition(100, 240);

    instruction.setFont(font);
    instruction.setString("Press ENTER to return to menu.");
    instruction.setCharacterSize(20);
    instruction.setFillColor(sf::Color(200, 200, 200));
    instruction.setPosition(100, 300);
}

void ResultsScreen::setResults(const std::string& algorithm, int numBars, double timeMs) {
    algoText.setString("Algorithm: " + algorithm);
    barsText.setString("Number of Bars: " + std::to_string(numBars));

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3) << timeMs << " ms";
    timeText.setString("Execution Time: " + oss.str());

    complexityText.setString("Time Complexity: " + getComplexity(algorithm));
}

void ResultsScreen::handleInput(sf::Event event) {
    // No special handling yet
}

void ResultsScreen::draw(sf::RenderWindow& window) {
    window.draw(title);
    window.draw(algoText);
    window.draw(barsText);
    window.draw(timeText);
    window.draw(complexityText);
    window.draw(instruction);
}

std::string ResultsScreen::getComplexity(const std::string& algorithm) {
    if (algorithm == "Bubble Sort") return "O(n^2)";
    if (algorithm == "Selection Sort") return "O(n^2)";
    if (algorithm == "Insertion Sort") return "O(n^2)";
    if (algorithm == "Merge Sort") return "O(n log n)";
    if (algorithm == "Quick Sort") return "O(n log n)";
    return "Unknown";
}
