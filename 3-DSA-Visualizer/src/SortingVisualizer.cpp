#include "SortingVisualizer.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

SortingVisualizer::SortingVisualizer(unsigned int numBars,
                                     unsigned int windowWidth,
                                     unsigned int windowHeight,
                                     const std::string& selectedAlgorithm)
    : winWidth(windowWidth), winHeight(windowHeight), algorithm(selectedAlgorithm)
{
    // Random init values (heights)
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(20.f, static_cast<float>(winHeight) - 80.f);

    values.resize(numBars);
    for (auto& v : values) v = dist(rng);
    originalValues = values;

    bars.resize(numBars);
    resizeBars();

    // Precompute the steps for the chosen algorithm using a working copy
    generateSteps();
}

void SortingVisualizer::resizeBars() {
    const float barW = static_cast<float>(winWidth) / static_cast<float>(values.size());
    for (size_t k = 0; k < bars.size(); ++k) {
        bars[k].setSize(sf::Vector2f(barW - 1.f, values[k]));
        bars[k].setPosition(static_cast<float>(k) * barW, static_cast<float>(winHeight) - values[k]);
        bars[k].setFillColor(sf::Color(100, 200, 120)); // base color
    }
}

void SortingVisualizer::resetBars() {
    values = originalValues;
    stepIndex = 0;
    finished = false;
    highlightA = highlightB = -1;
    resizeBars();
}

void SortingVisualizer::updateBarAt(int idx) {
    if (idx < 0 || idx >= static_cast<int>(bars.size())) return;
    const float barW = static_cast<float>(winWidth) / static_cast<float>(values.size());
    bars[idx].setSize(sf::Vector2f(barW - 1.f, values[idx]));
    bars[idx].setPosition(static_cast<float>(idx) * barW, static_cast<float>(winHeight) - values[idx]);
}

void SortingVisualizer::applyStep(const Step& s) {
    highlightA = s.a;
    highlightB = s.b;

    switch (s.type) {
        case StepType::Compare:
            // no data change, just highlight
            break;
        case StepType::Swap: {
            std::swap(values[s.a], values[s.b]);
            updateBarAt(s.a);
            updateBarAt(s.b);
            break;
        }
        case StepType::Overwrite: {
            values[s.a] = s.value;
            updateBarAt(s.a);
            break;
        }
    }
}

void SortingVisualizer::update(float dt) {
    if (finished) return;

    timer += dt;
    if (timer >= speed) {
        timer = 0.f;

        if (stepIndex < steps.size()) {
            applyStep(steps[stepIndex]);
            ++stepIndex;
        } else {
            finished = true;
            highlightA = highlightB = -1;
            // color everything as done (optional)
            for (auto& b : bars) b.setFillColor(sf::Color(120, 170, 255));
        }
    }
}

void SortingVisualizer::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < bars.size(); ++i) {
        if (static_cast<int>(i) == highlightA || static_cast<int>(i) == highlightB)
            bars[i].setFillColor(sf::Color::Red);
        else
            bars[i].setFillColor(sf::Color(100, 200, 120));

        window.draw(bars[i]);
    }
}

void SortingVisualizer::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::R) {
            resetBars();
        }
        if (event.key.code == sf::Keyboard::Up) {
            speed = std::max(0.001f, speed - 0.005f);
        }
        if (event.key.code == sf::Keyboard::Down) {
            speed = std::min(0.2f, speed + 0.005f);
        }
    }
}

/* -------------------- STEP GENERATION -------------------- */

void SortingVisualizer::generateSteps() {
    steps.clear();

    // use a working copy so we don't mutate the visual vector while recording
    std::vector<float> arr = originalValues;

    if (algorithm == "Bubble Sort")       genBubble(arr);
    else if (algorithm == "Selection Sort") genSelection(arr);
    else if (algorithm == "Insertion Sort") genInsertion(arr);
    else if (algorithm == "Merge Sort")     genMerge(arr);
    else if (algorithm == "Quick Sort")     genQuick(arr);
    else                                     genBubble(arr); // default
}

/* Bubble Sort */
void SortingVisualizer::genBubble(std::vector<float> arr) {
    const int n = static_cast<int>(arr.size());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            steps.push_back({StepType::Compare, j, j+1, 0.f});
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                steps.push_back({StepType::Swap, j, j+1, 0.f});
            }
        }
    }
}

/* Selection Sort */
void SortingVisualizer::genSelection(std::vector<float> arr) {
    const int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < n; ++j) {
            steps.push_back({StepType::Compare, minIdx, j, 0.f});
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
            steps.push_back({StepType::Swap, i, minIdx, 0.f});
        }
    }
}

/* Insertion Sort using adjacent swaps for visualization */
void SortingVisualizer::genInsertion(std::vector<float> arr) {
    const int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j > 0) {
            steps.push_back({StepType::Compare, j - 1, j, 0.f});
            if (arr[j - 1] > arr[j]) {
                std::swap(arr[j - 1], arr[j]);
                steps.push_back({StepType::Swap, j - 1, j, 0.f});
                --j;
            } else {
                break;
            }
        }
    }
}

/* Merge Sort: record overwrites */
void SortingVisualizer::genMerge(std::vector<float> arr) {
    mergeRec(arr, 0, static_cast<int>(arr.size()) - 1);
}

void SortingVisualizer::mergeRec(std::vector<float>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeRec(arr, l, m);
    mergeRec(arr, m + 1, r);
    mergeDo(arr, l, m, r);
}

void SortingVisualizer::mergeDo(std::vector<float>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<float> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        steps.push_back({StepType::Compare, l + i, m + 1 + j, 0.f});
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            steps.push_back({StepType::Overwrite, k, -1, L[i]});
            ++i;
        } else {
            arr[k] = R[j];
            steps.push_back({StepType::Overwrite, k, -1, R[j]});
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        arr[k] = L[i];
        steps.push_back({StepType::Overwrite, k, -1, L[i]});
        ++i; ++k;
    }
    while (j < n2) {
        arr[k] = R[j];
        steps.push_back({StepType::Overwrite, k, -1, R[j]});
        ++j; ++k;
    }
}

/* Quick Sort */
void SortingVisualizer::genQuick(std::vector<float> arr) {
    quickRec(arr, 0, static_cast<int>(arr.size()) - 1);
}

void SortingVisualizer::quickRec(std::vector<float>& arr, int l, int r) {
    if (l >= r) return;
    int p = quickPartition(arr, l, r);
    quickRec(arr, l, p - 1);
    quickRec(arr, p + 1, r);
}

int SortingVisualizer::quickPartition(std::vector<float>& arr, int l, int r) {
    float pivot = arr[r];
    int i = l - 1;
    for (int j = l; j < r; ++j) {
        steps.push_back({StepType::Compare, j, r, 0.f}); // compare with pivot
        if (arr[j] < pivot) {
            ++i;
            if (i != j) {
                std::swap(arr[i], arr[j]);
                steps.push_back({StepType::Swap, i, j, 0.f});
            }
        }
    }
    if (i + 1 != r) {
        std::swap(arr[i + 1], arr[r]);
        steps.push_back({StepType::Swap, i + 1, r, 0.f});
    }
    return i + 1;
}
