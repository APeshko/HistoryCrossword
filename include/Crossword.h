#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>

struct Cell {
    char letter;
    bool isActive;
    bool isEditable;
    int number;
    sf::Vector2i position;
    sf::RectangleShape shape;
    sf::Text letterText;
    sf::Text numberText;
};

struct Word {
    std::string word;
    std::string clue;
    std::vector<sf::Vector2i> positions;
    bool isHorizontal;
    bool isSolved;
};

class Crossword {
public:
    Crossword(int rows, int cols);
    void loadFromWords(const std::vector<Word>& words);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);
    bool checkSolution();
    void clear();
    void setFont(const sf::Font& font);

private:
    void placeWord(const Word& word);
    void updateCellTexts();
    bool isCellActive(int row, int col) const;
    void selectCell(int row, int col);

    int rows;
    int cols;
    float cellSize;
    sf::Vector2f startPos;
    std::vector<std::vector<Cell>> grid;
    std::vector<Word> words;
    sf::Vector2i selectedCell;
    const sf::Font* font;
    std::unordered_map<int, Word*> numberedWords;
    int currentNumber;
};
