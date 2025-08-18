#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "SortingVisualizer.hpp"
#include "Menu.h"
#include "SettingsScreen.hpp"
#include "ResultsScreen.hpp"

enum class AppState {
    MENU,
    VISUALIZING,
    RESULTS
};

int main() {
    const unsigned int WIDTH  = 1280;
    const unsigned int HEIGHT = 720;

    sf::RenderWindow window(
        sf::VideoMode(WIDTH, HEIGHT),
        "DSA Visualizer",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setVerticalSyncEnabled(true);

    AppState appState = AppState::MENU;

    Menu menu;
    ResultsScreen resultsScreen;

    std::string selectedAlgorithm;
    int numBars = 50;

    sf::Clock deltaClock;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;

    SortingVisualizer* sortingVis = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            switch (appState) {
                case AppState::MENU: {
                    menu.handleInput(event, window);

                    // Start on Enter or click "Start Visualization"
                    bool enterPressed = (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter);
                    bool mouseStart   = (event.type == sf::Event::MouseButtonPressed &&
                                         event.mouseButton.button == sf::Mouse::Left &&
                                         menu.isStartSelected());

                    if (enterPressed || mouseStart) {
                        selectedAlgorithm = menu.getSelectedAlgorithm();
                        numBars = menu.getNumBars();

                        delete sortingVis;
                        sortingVis = new SortingVisualizer(numBars, WIDTH, HEIGHT, selectedAlgorithm);

                        startTime = std::chrono::high_resolution_clock::now();
                        appState = AppState::VISUALIZING;
                    }
                } break;

                case AppState::VISUALIZING: {
                    if (sortingVis) {
                        sortingVis->handleEvent(event);
                    }
                } break;

                case AppState::RESULTS: {
                    bool back = false;
                    resultsScreen.handleInput(event, back, window);
                    if (back) {
                        appState = AppState::MENU;
                    }
                } break;
            }
        }

        float dt = deltaClock.restart().asSeconds();

        window.clear(sf::Color(20, 24, 32));

        switch (appState) {
            case AppState::MENU:
                menu.draw(window);
                break;

            case AppState::VISUALIZING:
                if (sortingVis) {
                    sortingVis->update(dt);
                    sortingVis->draw(window);

                    if (sortingVis->isFinished()) {
                        endTime = std::chrono::high_resolution_clock::now();
                  double duration = std::chrono::duration<double>(endTime - startTime).count();


                        resultsScreen.setResults(selectedAlgorithm, numBars, duration);

                        delete sortingVis;
                        sortingVis = nullptr;
                        appState = AppState::RESULTS;
                    }
                }
                break;

            case AppState::RESULTS:
                resultsScreen.draw(window);
                break;
        }

        window.display();
    }

    delete sortingVis;
    return 0;
}
