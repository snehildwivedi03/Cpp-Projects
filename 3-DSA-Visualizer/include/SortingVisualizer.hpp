#pragma once
#include "Visualizer.hpp"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class SortingVisualizer : public Visualizer {
public:
    SortingVisualizer(unsigned int numBars,
                      unsigned int windowWidth,
                      unsigned int windowHeight,
                      const std::string& selectedAlgorithm);

    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event) override;

    bool isFinished() const { return finished; }

private:
    enum class StepType { Compare, Swap, Overwrite };

    struct Step {
        StepType type;
        int a;
        int b;
        float value;  // used for Overwrite
    };

    std::vector<float> values;              // current visual values
    std::vector<float> originalValues;      // initial randomized values (for step generation)
    std::vector<sf::RectangleShape> bars;

    std::vector<Step> steps; // precomputed steps for the chosen algorithm
    size_t stepIndex = 0;

    unsigned int winWidth, winHeight;
    std::string algorithm;

    // timing
    float speed = 0.01f; // seconds per step
    float timer = 0.f;
    bool finished = false;

    // rendering helpers
    int highlightA = -1, highlightB = -1; // indices to color for compare/swap

    void resetBars();
    void resizeBars();

    // step application
    void applyStep(const Step& s);

    // bar updates
    void updateBarAt(int idx);

    // step generators (operate on a working copy)
    void generateSteps();

    void genBubble(std::vector<float> arr);
    void genSelection(std::vector<float> arr);
    void genInsertion(std::vector<float> arr);
    void genMerge(std::vector<float> arr);
    void mergeRec(std::vector<float>& arr, int l, int r);
    void mergeDo(std::vector<float>& arr, int l, int m, int r);

    void genQuick(std::vector<float> arr);
    void quickRec(std::vector<float>& arr, int l, int r);
    int  quickPartition(std::vector<float>& arr, int l, int r);
};
