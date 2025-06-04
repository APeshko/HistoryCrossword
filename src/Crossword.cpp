#include "../include/Crossword.h"
#include "../include/utils.h"
#include <algorithm>

Crossword::Crossword(const std::vector<CrosswordDefinition>& definitions, int gridSize) 
    : definitions(definitions), gridSize(gridSize), cellSize(40), 
      selectedX(-1), selectedY(-1), isFullyCompleted(false) {
    
    initializeGrid();
}

void Crossword::initializeGrid() {
    grid.resize(gridSize, std::vector<Cell>(gridSize));
    
    for (int i = 0; i < definitions.size(); ++i) {
        const auto& def = definitions[i];
        int x = def.startX;
        int y = def.startY;
        
        for (char c : def.word) {
            if (x >= gridSize || y >= gridSize) break;
            
            grid[y][x].letter = c;
            grid[y][x].isEditable = true;
            grid[y][x].wordIndices.push_back(i);
            
            if (def.horizontal) x++;
            else y++;
        }
    }
    
    completedWords.clear();
    for (int i = 0; i < definitions.size(); ++i) {
        completedWords[i] = false;
    }
}

void Crossword::draw(sf::RenderWindow& window, const sf::Font& font) {
    drawGrid(window);
    drawLetters(window, font);
    drawDefinitions(window, font);
}

void Crossword::drawGrid(sf::RenderWindow& window) const {
    // Draw grid lines
    sf::RectangleShape line(sf::Vector2f(gridSize * cellSize, 1));
    line.setFillColor(sf::Color::Black);
    
    for (int i = 0; i <= gridSize; ++i) {
        // Horizontal lines
        line.setSize(sf::Vector2f(gridSize * cellSize, 1));
        line.setPosition(0, i * cellSize);
        window.draw(line);
        
        // Vertical lines
        line.setSize(sf::Vector2f(1, gridSize * cellSize));
        line.setPosition(i * cellSize, 0);
        window.draw(line);
    }
    
    // Draw cells
    sf::RectangleShape cell(sf::Vector2f(cellSize - 2, cellSize - 2));
    
    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            if (grid[y][x].isEditable) {
                cell.setPosition(x * cellSize + 1, y * cellSize + 1);
                
                if (x == selectedX && y == selectedY) {
                    cell.setFillColor(sf::Color(200, 230, 255));
                } else if (grid[y][x].isHighlighted) {
                    cell.setFillColor(sf::Color(230, 230, 230));
                } else {
                    cell.setFillColor(sf::Color::White);
                }
                
                window.draw(cell);
            }
        }
    }
}

void Crossword::drawLetters(sf::RenderWindow& window, const sf::Font& font) const {
    sf::Text letterText;
    letterText.setFont(font);
    letterText.setCharacterSize(24);
    letterText.setFillColor(sf::Color::Black);
    
    for (int y = 0; y < gridSize; ++y) {
        for (int x = 0; x < gridSize; ++x) {
            if (grid[y][x].isEditable && !grid[y][x].userInput.empty()) {
                letterText.setString(grid[y][x].userInput);
                letterText.setPosition(x * cellSize + cellSize / 2 - 8, y * cellSize + cellSize / 2 - 15);
                window.draw(letterText);
            }
        }
    }
}

void Crossword::drawDefinitions(sf::RenderWindow& window, const sf::Font& font) const {
    sf::Text defText;
    defText.setFont(font);
    defText.setCharacterSize(20);
    defText.setFillColor(sf::Color::Black);
    
    int startY = gridSize * cellSize + 20;
    int startX = 20;
    
    defText.setString("По горизонтали:");
    defText.setPosition(startX, startY);
    window.draw(defText);
    
    startY += 30;
    
    for (int i = 0; i < definitions.size(); ++i) {
        const auto& def = definitions[i];
        if (!def.horizontal) continue;
        
        std::string defStr = std::to_string(i + 1) + ". " + def.definition;
        if (completedWords.at(i)) {
            defStr += " (решено)";
            defText.setFillColor(sf::Color::Green);
        } else {
            defText.setFillColor(sf::Color::Black);
        }
        
        defText.setString(defStr);
        defText.setPosition(startX, startY);
        window.draw(defText);
        
        startY += 25;
    }
    
    startY += 10;
    defText.setString("По вертикали:");
    defText.setPosition(startX, startY);
    defText.setFillColor(sf::Color::Black);
    window.draw(defText);
    
    startY += 30;
    
    for (int i = 0; i < definitions.size(); ++i) {
        const auto& def = definitions[i];
        if (def.horizontal) continue;
        
        std::string defStr = std::to_string(i + 1) + ". " + def.definition;
        if (completedWords.at(i)) {
            defStr += " (решено)";
            defText.setFillColor(sf::Color::Green);
        } else {
            defText.setFillColor(sf::Color::Black);
        }
        
        defText.setString(defStr);
        defText.setPosition(startX, startY);
        window.draw(defText);
        
        startY += 25;
    }
}

void Crossword::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int x = mousePos.x / cellSize;
        int y = mousePos.y / cellSize;
        
        if (x >= 0 && x < gridSize && y >= 0 && y < gridSize && grid[y][x].isEditable) {
            selectedX = x;
            selectedY = y;
            updateHighlight(x, y);
        }
    }
    else if (event.type == sf::Event::TextEntered && selectedX != -1 && selectedY != -1) {
        wchar_t c = event.text.unicode;
        
        if (utils::isCyrillic(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            grid[selectedY][selectedX].userInput = utils::toUpper(static_cast<char>(c));
            
            // Move to next cell if possible
            for (int wordIdx : grid[selectedY][selectedX].wordIndices) {
                const auto& def = definitions[wordIdx];
                int nextX = selectedX;
                int nextY = selectedY;
                
                if (def.horizontal) nextX++;
                else nextY++;
                
                if (nextX < gridSize && nextY < gridSize && grid[nextY][nextX].isEditable) {
                    selectedX = nextX;
                    selectedY = nextY;
                    updateHighlight(selectedX, selectedY);
                    break;
                }
            }
            
            checkCompletion();
        }
        else if (c == 8) { // Backspace
            grid[selectedY][selectedX].userInput.clear();
            
            // Move to previous cell if possible
            for (int wordIdx : grid[selectedY][selectedX].wordIndices) {
                const auto& def = definitions[wordIdx];
                int prevX = selectedX;
                int prevY = selectedY;
                
                if (def.horizontal) prevX--;
                else prevY--;
                
                if (prevX >= 0 && prevY >= 0 && grid[prevY][prevX].isEditable) {
                    selectedX = prevX;
                    selectedY = prevY;
                    updateHighlight(selectedX, selectedY);
                    break;
                }
            }
        }
    }
}

void Crossword::updateHighlight(int x, int y) {
    // Clear all highlights
    for (auto& row : grid) {
        for (auto& cell : row) {
            cell.isHighlighted = false;
        }
    }
    
    // Highlight all cells in the same words
    for (int wordIdx : grid[y][x].wordIndices) {
        const auto& def = definitions[wordIdx];
        int cx = def.startX;
        int cy = def.startY;
        
        for (char c : def.word) {
            if (cx >= gridSize || cy >= gridSize) break;
            
            grid[cy][cx].isHighlighted = true;
            
            if (def.horizontal) cx++;
            else cy++;
        }
    }
}

void Crossword::checkCompletion() {
    isFullyCompleted = true;
    
    for (int i = 0; i < definitions.size(); ++i) {
        const auto& def = definitions[i];
        int x = def.startX;
        int y = def.startY;
        bool complete = true;
        
        for (char c : def.word) {
            if (x >= gridSize || y >= gridSize) {
                complete = false;
                break;
            }
            
            if (grid[y][x].userInput.empty() || grid[y][x].userInput[0] != c) {
                complete = false;
                break;
            }
            
            if (def.horizontal) x++;
            else y++;
        }
        
        completedWords[i] = complete;
        if (!complete) isFullyCompleted = false;
    }
}

bool Crossword::isComplete() const {
    return isFullyCompleted;
}

void Crossword::reset() {
    for (auto& row : grid) {
        for (auto& cell : row) {
            cell.userInput.clear();
        }
    }
    
    for (auto& pair : completedWords) {
        pair.second = false;
    }
    
    isFullyCompleted = false;
    selectedX = -1;
    selectedY = -1;
}
