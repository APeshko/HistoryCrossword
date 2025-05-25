#ifndef CROSSWORDDATA_H
#define CROSSWORDDATA_H

#include "icrossword.h"
#include "question.h"
#include <QVector>

class CrosswordData : public ICrossword {
public:
    CrosswordData(const QString& title, 
                 const QVector<QVector<QChar>>& grid,
                 const std::vector<Question>& questions);
    
    const std::vector<Question>& getQuestions() const override;
    QChar cellAt(int row, int col) const override;
    int rows() const override;
    int cols() const override;
    QString title() const override;

private:
    std::vector<Question> m_questions;
    QVector<QVector<QChar>> m_grid;
    QString m_title;
};

#endif // CROSSWORDDATA_H
