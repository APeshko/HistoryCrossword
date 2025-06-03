#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <vector>
#include <string>
#include <functional>

class Crossword {
public:
    using BackCallback = std::function<void()>;

    Crossword(const std::vector<std::string>& grid, 
             const std::vector<std::string>& acrossClues,
             const std::vector<std::string>& downClues);

    const std::vector<std::string>& getGrid() const;
    const std::vector<std::string>& getAcrossClues() const;
    const std::vector<std::string>& getDownClues() const;
    bool isCompleted() const;
    bool hasSelectedCell() const;
    std::pair<size_t, size_t> getSelectedCell() const;
    const std::string& getCurrentInput() const;
    bool isCellSelected(size_t x, size_t y) const;
    bool isCellInCurrentWord(size_t x, size_t y) const;

    void selectCell(size_t x, size_t y);
    void addLetter(char c);
    void removeLetter();
    void requestBack();
    void setBackCallback(BackCallback callback);

private:
    std::vector<std::string> m_grid;
    std::vector<std::string> m_solution;
    std::vector<std::string> m_acrossClues;
    std::vector<std::string> m_downClues;
    std::pair<size_t, size_t> m_selectedCell;
    bool m_isHorizontal;
    std::string m_currentInput;
    BackCallback m_backCallback;

    void updateInput();
    bool checkSolution() const;
    std::vector<std::pair<size_t, size_t>> getCurrentWordCells() const;
};

#endif // CROSSWORD_H
