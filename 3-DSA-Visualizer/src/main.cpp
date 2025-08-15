#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "SortingVisualizer.hpp"
#include "Menu.h"
#include "SettingsScreen.hpp"  // new header for bar selection
#include "ResultsScreen.hpp"   // new header for showing results

enum class AppState {
    MENU,
    SETTINGS,
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
    SettingsScreen settingsScreen;
    ResultsScreen resultsScreen;

    std::string selectedAlgorithm;
    int numBars = 50;

    bool paused = false;
    sf::Clock deltaClock;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;

    SortingVisualizer* sortingVis = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            switch (appState) {
                case AppState::MENU:
                    menu.handleInput(event);
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                        selectedAlgorithm = menu.getSelectedAlgorithm();
                        appState = AppState::SETTINGS;
                    }
                    break;

                case AppState::SETTINGS:
                    settingsScreen.handleInput(event);
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                        numBars = settingsScreen.getNumBars();
                        sortingVis = new SortingVisualizer(numBars, WIDTH, HEIGHT, selectedAlgorithm);
                        startTime = std::chrono::high_resolution_clock::now();
                        appState = AppState::VISUALIZING;
                    }
                    break;

                case AppState::VISUALIZING:
                    sortingVis->handleEvent(event);
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        endTime = std::chrono::high_resolution_clock::now();
                        double duration = std::chrono::duration<double, std::milli>(endTime - startTime).count();
                        resultsScreen.setResults(selectedAlgorithm, numBars, duration);
                        delete sortingVis;
                        sortingVis = nullptr;
                        appState = AppState::RESULTS;
                    }
                    break;

                case AppState::RESULTS:
                    resultsScreen.handleInput(event);
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                        appState = AppState::MENU; // restart
                    }
                    break;
            }
        }

        float dt = deltaClock.restart().asSeconds();
        if (paused) dt = 0.f;

        window.clear(sf::Color(20, 24, 32));

        switch (appState) {
            case AppState::MENU:
                menu.draw(window);
                break;

            case AppState::SETTINGS:
                settingsScreen.draw(window);
                break;

            case AppState::VISUALIZING:
                sortingVis->update(dt);
                sortingVis->draw(window);
                break;

            case AppState::RESULTS:
                resultsScreen.draw(window);
                break;
        }

        window.display();
    }

    if (sortingVis) delete sortingVis;
    return 0;
}
