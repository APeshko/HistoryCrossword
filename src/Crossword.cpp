#include "Crossword.h"
#include <algorithm>

Crossword::Crossword(int rows, int cols) 
    : rows(rows), cols(cols), cellSize(40.f), startPos(150.f, 150.f), selectedCell(-1, -1), currentNumber(1) {
    grid.resize(rows, std::vector<Cell>(cols));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j].letter = ' ';
            grid[i][j].isActive = false;
            grid[i][j].isEditable = false;
            grid[i][j].number = 0;
            grid[i][j].position = sf::Vector2i(j, i);
            
            grid[i][j].shape.setSize(sf::Vector2f(cellSize, cellSize));
            grid[i][j].shape.setPosition(startPos.x + j * cellSize, startPos.y + i * cellSize);
            grid[i][j].shape.setFillColor(sf::Color::White);
            grid[i][j].shape.setOutlineThickness(1.f);
            grid[i][j].shape.setOutlineColor(sf::Color::Black);
            
            grid[i][j].letterText.setString("");
            grid[i][j].letterText.setCharacterSize(24);
            grid[i][j].letterText.setFillColor(sf::Color::Black);
            
            grid[i][j].numberText.setString("");
            grid[i][j].numberText.setCharacterSize(10);
            grid[i][j].numberText.setFillColor(sf::Color::Black);
        }
    }
}

void Crossword::setFont(const sf::Font& font) {
    this->font = &font;
    for (auto& row : grid) {
        for (auto& cell : row) {
            cell.letterText.setFont(font);
            cell.numberText.setFont(font);
        }
    }
}

void Crossword::loadFromWords(const std::vector<Word>& words) {
    this->words.clear();
    currentNumber = 1;
    
    for (const auto& word : words) {
        Word newWord = word;
        newWord.isSolved = false;
        this->words.push_back(newWord);
        placeWord(newWord);
    }
    
    updateCellTexts();
}

void Crossword::placeWord(const Word& word) {
    bool isFirstLetter = true;
    int x = word.positions[0].x;
    int y = word.positions[0].y;
    
    for (size_t i = 0; i < word.word.size(); ++i) {
        if (word.isHorizontal) {
            x = word.positions[i].x;
        } else {
            y = word.positions[i].y;
        }
        
        if (y >= 0 && y < rows && x >= 0 && x < cols) {
            grid[y][x].letter = toupper(word.word[i]);
            grid[y][x].isActive = true;
            grid[y][x].isEditable = true;
            
            if (isFirstLetter) {
                grid[y][x].number = currentNumber;
                numberedWords[currentNumber] = &this->words.back();
                currentNumber++;
                isFirstLetter = false;
            }
        }
    }
}

void Crossword::updateCellTexts() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j].isActive) {
                grid[i][j].letterText.setString(std::string(1, grid[i][j].letter));
                grid[i][j].letterText.setPosition(
                    startPos.x + j * cellSize + cellSize / 2 - grid[i][j].letterText.getGlobalBounds().width / 2,
                    startPos.y + i * cellSize + cellSize / 2 - grid[i][j].letterText.getGlobalBounds().height / 2 - 5
                );
                
                if (grid[i][j].number > 0) {
                    grid[i][j].numberText.setString(std::to_string(grid[i][j].number));
                    grid[i][j].numberText.setPosition(
                        startPos.x + j * cellSize + 2,
                        startPos.y + i * cellSize + 2
                    );
                }
            }
        }
    }
}

bool Crossword::isCellActive(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols && grid[row][col].isActive;
}

void Crossword::selectCell(int row, int col) {
    if (selectedCell.x != -1 && selectedCell.y != -1) {
        grid[selectedCell.y][selectedCell.x].shape.setFillColor(sf::Color::White);
    }
    
    selectedCell = sf::Vector2i(col, row);
    
    if (selectedCell.x != -1 && selectedCell.y != -1) {
        grid[selectedCell.y][selectedCell.x].shape.setFillColor(sf::Color(200, 230, 255));
    }
}

void Crossword::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
            
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (grid[i][j].shape.getGlobalBounds().contains(mousePos) && grid[i][j].isEditable) {
                        selectCell(i, j);
                        return;
                    }
                }
            }
        }
    }
    else if (event.type == sf::Event::TextEntered && selectedCell.x != -1 && selectedCell.y != -1) {
        if (event.text.unicode >= 'а' && event.text.unicode <= 'я') {
            grid[selectedCell.y][selectedCell.x].letter = toupper(static_cast<char>(event.text.unicode));
            updateCellTexts();
        }
        else if (event.text.unicode >= 'А' && event.text.unicode <= 'Я') {
            grid[selectedCell.y][selectedCell.x].letter = static_cast<char>(event.text.unicode);
            updateCellTexts();
        }
        else if (event.text.unicode == 8) { // Backspace
            grid[selectedCell.y][selectedCell.x].letter = ' ';
            updateCellTexts();
        }
    }
}

void Crossword::render(sf::RenderWindow& window) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j].isActive) {
                window.draw(grid[i][j].shape);
                if (grid[i][j].letter != ' ') {
                    window.draw(grid[i][j].letterText);
                }
                if (grid[i][j].number > 0) {
                    window.draw(grid[i][j].numberText);
                }
            }
        }
    }
}

bool Crossword::checkSolution() {
    bool allCorrect = true;
    
    for (auto& word : words) {
        bool wordCorrect = true;
        
        for (size_t i = 0; i < word.word.size(); ++i) {
            int x = word.isHorizontal ? word.positions[i].x : word.positions[0].x;
            int y = word.isHorizontal ? word.positions[0].y : word.positions[i].y;
            
            if (y >= 0 && y < rows && x >= 0 && x < cols) {
                if (toupper(word.word[i]) != grid[y][x].letter) {
                    wordCorrect = false;
                    break;
                }
            }
        }
        
        word.isSolved = wordCorrect;
        if (!wordCorrect) {
            allCorrect = false;
        }
    }
    
    return allCorrect;
}

void Crossword::clear() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j].isEditable) {
                grid[i][j].letter = ' ';
            }
        }
    }
    updateCellTexts();
}
