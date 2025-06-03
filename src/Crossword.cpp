#include "Crossword.h"
#include <algorithm>

Crossword::Crossword(const std::vector<std::string>& grid, 
                     const std::vector<std::string>& acrossClues,
                     const std::vector<std::string>& downClues)
    : m_grid(grid), m_acrossClues(acrossClues), m_downClues(downClues), 
      m_selectedCell({-1, -1}), m_isHorizontal(true) {
    
    // Create solution grid (initially empty)
    m_solution = grid;
    for (auto& row : m_solution) {
        std::replace(row.begin(), row.end(), '.', ' ');
        std::replace(row.begin(), row.end(), '#', ' ');
    }
}

const std::vector<std::string>& Crossword::getGrid() const {
    return m_grid;
}

const std::vector<std::string>& Crossword::getAcrossClues() const {
    return m_acrossClues;
}

const std::vector<std::string>& Crossword::getDownClues() const {
    return m_downClues;
}

bool Crossword::isCompleted() const {
    return checkSolution();
}

bool Crossword::hasSelectedCell() const {
    return m_selectedCell.first != static_cast<size_t>(-1);
}

std::pair<size_t, size_t> Crossword::getSelectedCell() const {
    return m_selectedCell;
}

const std::string& Crossword::getCurrentInput() const {
    return m_currentInput;
}

bool Crossword::isCellSelected(size_t x, size_t y) const {
    return m_selectedCell.first == x && m_selectedCell.second == y;
}

bool Crossword::isCellInCurrentWord(size_t x, size_t y) const {
    if (!hasSelectedCell()) return false;
    
    auto wordCells = getCurrentWordCells();
    return std::find(wordCells.begin(), wordCells.end(), std::make_pair(x, y)) != wordCells.end();
}

void Crossword::selectCell(size_t x, size_t y) {
    if (m_grid[y][x] == '#') return;

    m_selectedCell = {x, y};
    
    // Determine direction based on adjacent cells
    bool canGoHorizontal = (x < m_grid[y].size() - 1 && m_grid[y][x + 1] != '#') || 
                          (x > 0 && m_grid[y][x - 1] != '#');
    bool canGoVertical = (y < m_grid.size() - 1 && m_grid[y + 1][x] != '#') || 
                         (y > 0 && m_grid[y - 1][x] != '#');

    // Prefer horizontal if both directions are possible
    m_isHorizontal = canGoHorizontal || !canGoVertical;
    
    updateInput();
}

void Crossword::addLetter(char c) {
    if (!hasSelectedCell()) return;

    auto wordCells = getCurrentWordCells();
    auto it = std::find(wordCells.begin(), wordCells.end(), m_selectedCell);
    if (it == wordCells.end()) return;

    size_t pos = std::distance(wordCells.begin(), it);
    if (pos >= m_currentInput.size()) {
        m_currentInput.resize(pos + 1, ' ');
    }
    m_currentInput[pos] = c;

    // Update solution grid
    auto [x, y] = wordCells[pos];
    m_solution[y][x] = c;

    // Move to next cell
    if (m_isHorizontal && x < m_grid[y].size() - 1 && m_grid[y][x + 1] != '#') {
        m_selectedCell = {x + 1, y};
    } else if (!m_isHorizontal && y < m_grid.size() - 1 && m_grid[y + 1][x] != '#') {
        m_selectedCell = {x, y + 1};
    }

    updateInput();
}

void Crossword::removeLetter() {
    if (!hasSelectedCell()) return;

    auto wordCells = getCurrentWordCells();
    auto it = std::find(wordCells.begin(), wordCells.end(), m_selectedCell);
    if (it == wordCells.end()) return;

    size_t pos = std::distance(wordCells.begin(), it);
    if (pos < m_currentInput.size()) {
        m_currentInput[pos] = ' ';
        
        // Update solution grid
        auto [x, y] = wordCells[pos];
        m_solution[y][x] = ' ';
    }

    // Move to previous cell
    if (pos > 0) {
        m_selectedCell = wordCells[pos - 1];
    }

    updateInput();
}

void Crossword::requestBack() {
    if (m_backCallback) {
        m_backCallback();
    }
}

void Crossword::setBackCallback(BackCallback callback) {
    m_backCallback = callback;
}

void Crossword::updateInput() {
    m_currentInput.clear();
    if (!hasSelectedCell()) return;

    auto wordCells = getCurrentWordCells();
    m_currentInput.resize(wordCells.size(), ' ');

    for (size_t i = 0; i < wordCells.size(); ++i) {
        auto [x, y] = wordCells[i];
        m_currentInput[i] = m_solution[y][x];
    }
}

bool Crossword::checkSolution() const {
    for (size_t y = 0; y < m_grid.size(); ++y) {
        for (size_t x = 0; x < m_grid[y].size(); ++x) {
            if (m_grid[y][x] != '#' && m_grid[y][x] != '.' && m_grid[y][x] != m_solution[y][x]) {
                return false;
            }
        }
    }
    return true;
}

std::vector<std::pair<size_t, size_t>> Crossword::getCurrentWordCells() const {
    std::vector<std::pair<size_t, size_t>> cells;
    if (!hasSelectedCell()) return cells;

    auto [startX, startY] = m_selectedCell;

    // Find start of the word
    if (m_isHorizontal) {
        while (startX > 0 && m_grid[startY][startX - 1] != '#') {
            --startX;
        }
    } else {
        while (startY > 0 && m_grid[startY - 1][startX] != '#') {
            --startY;
        }
    }

    // Collect all cells in the word
    size_t x = startX;
    size_t y = startY;
    while (x < m_grid[y].size() && y < m_grid.size() && m_grid[y][x] != '#') {
        cells.emplace_back(x, y);
        if (m_isHorizontal) {
            ++x;
        } else {
            ++y;
        }
    }

    return cells;
}
