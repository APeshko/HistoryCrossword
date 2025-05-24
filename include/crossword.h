#ifndef CROSSWORD_H
#define CROSSWORD_H

#include "question.h"
#include <vector>
#include <QString>
#include <QJsonObject>

class Crossword {
public:
    Crossword();
    bool loadFromJson(const QString& filePath);
    const std::vector<Question>& getQuestions() const;
    const QChar& cellAt(int row, int col) const;
    int rows() const;
    int cols() const;
    QString title() const;

private:
    std::vector<Question> questions;
    QVector<QVector<QChar>> grid;
    QString m_title;
    void buildGrid();
};

#endif // CROSSWORD_H
