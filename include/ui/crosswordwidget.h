#ifndef CROSSWORDWIDGET_H
#define CROSSWORDWIDGET_H

#include <QWidget>
#include "crossword.h"

class QGridLayout;
class QLineEdit;
class QLabel;

class CrosswordWidget : public QWidget {
    Q_OBJECT
public:
    explicit CrosswordWidget(QWidget *parent = nullptr);
    void setCrossword(const Crossword& crossword);
    void checkAnswers();

private:
    void setupUI();
    void createGrid();
    void createQuestionsList();

    Crossword currentCrossword;
    QGridLayout *gridLayout;
    QVector<QVector<QLineEdit*>> cells;
    QLabel *questionsLabel;
};

#endif // CROSSWORDWIDGET_H
