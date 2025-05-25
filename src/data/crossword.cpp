#include "crossworddata.h"

CrosswordData::CrosswordData(const QString& title,
                           const QVector<QVector<QChar>>& grid,
                           const std::vector<Question>& questions)
    : m_title(title), m_grid(grid), m_questions(questions) {}

const std::vector<Question>& CrosswordData::getQuestions() const {
    return m_questions;
}

QChar CrosswordData::cellAt(int row, int col) const {
    return m_grid[row][col];
}

int CrosswordData::rows() const {
    return m_grid.size();
}

int CrosswordData::cols() const {
    return m_grid.isEmpty() ? 0 : m_grid[0].size();
}

QString CrosswordData::title() const {
    return m_title;
}
