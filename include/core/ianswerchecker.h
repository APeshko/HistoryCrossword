#ifndef IANSWERCHECKER_H
#define IANSWERCHECKER_H

#include <QVector>
#include <QWidget>

class IAnswerChecker {
public:
    virtual ~IAnswerChecker() = default;
    virtual void checkAnswers(const QVector<QVector<QWidget*>>& cells, 
                            const ICrossword* crossword) = 0;
};

#endif // IANSWERCHECKER_H
