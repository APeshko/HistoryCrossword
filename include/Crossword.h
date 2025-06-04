#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <memory>

struct CrosswordDefinition {
    std::string word;
    std::string definition;
    int startX;
    int startY;
    bool horizontal;
};

class Crossword {
public:
    Crossword(const std::vector<CrosswordDefinition>& definitions, int gridSize);
    
    void draw(sf::RenderWindow& window, const sf::Font& font);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    bool isComplete() const;
    void reset();

private:
    struct Cell {
        char letter;
        bool isEditable;
        bool isHighlighted;
        std::string userInput;
        std::vector<int> wordIndices;
    };

    void initializeGrid();
    void updateHighlight(int x, int y);
    void checkCompletion();
    void drawGrid(sf::RenderWindow& window) const;
    void drawDefinitions(sf::RenderWindow& window, const sf::Font& font) const;
    void drawLetters(sf::RenderWindow& window, const sf::Font& font) const;

    std::vector<std::vector<Cell>> grid;
    std::vector<CrosswordDefinition> definitions;
    std::map<int, bool> completedWords;
    int gridSize;
    int cellSize;
    int selectedX;
    int selectedY;
    bool isFullyCompleted;
};

#endif // CROSSWORD_H
