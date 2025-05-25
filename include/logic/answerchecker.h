#ifndef ANSWERCHECKER_H
#define ANSWERCHECKER_H

#include "ianswerchecker.h"
#include <QMessageBox>

class BasicAnswerChecker : public IAnswerChecker {
public:
    void checkAnswers(const QVector<QVector<QWidget*>>& cells, 
                     const ICrossword* crossword) override;
};

#endif // ANSWERCHECKER_H
