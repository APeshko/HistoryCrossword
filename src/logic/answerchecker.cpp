#include "answerchecker.h"
#include <QLineEdit>
#include <QMessageBox>

void BasicAnswerChecker::checkAnswers(const QVector<QVector<QWidget*>>& cells, 
                                    const ICrossword* crossword) {
    int correct = 0;
    int total = 0;
    
    for (int row = 0; row < cells.size(); ++row) {
        for (int col = 0; col < cells[row].size(); ++col) {
            if (cells[row][col]) {
                total++;
                QLineEdit* lineEdit = qobject_cast<QLineEdit*>(cells[row][col]);
                if (lineEdit) {
                    QString userAnswer = lineEdit->text().toUpper();
                    QChar correctAnswer = crossword->cellAt(row, col);
                    
                    if (userAnswer == correctAnswer) {
                        correct++;
                        lineEdit->setStyleSheet("background-color: lightgreen;");
                    } else {
                        lineEdit->setStyleSheet("background-color: pink;");
                    }
                }
            }
        }
    }
    
    int percentage = total > 0 ? (correct * 100) / total : 0;
    QMessageBox::information(nullptr, "Результат", 
        QString("Правильно: %1 из %2 (%3%)").arg(correct).arg(total).arg(percentage));
}
