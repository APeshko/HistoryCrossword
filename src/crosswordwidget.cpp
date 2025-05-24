#include "crosswordwidget.h"
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include <QRegularExpressionValidator>

CrosswordWidget::CrosswordWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void CrosswordWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title label will be set when crossword is loaded
    QLabel *titleLabel = new QLabel(this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    QHBoxLayout *contentLayout = new QHBoxLayout();
    
    // Grid area
    QWidget *gridWidget = new QWidget();
    gridLayout = new QGridLayout(gridWidget);
    gridLayout->setSpacing(2);
    contentLayout->addWidget(gridWidget, 3);
    
    // Questions area
    QScrollArea *scrollArea = new QScrollArea();
    QWidget *questionsWidget = new QWidget();
    QVBoxLayout *questionsLayout = new QVBoxLayout(questionsWidget);
    
    questionsLabel = new QLabel();
    questionsLabel->setWordWrap(true);
    questionsLayout->addWidget(questionsLabel);
    
    QPushButton *checkButton = new QPushButton("Проверить ответы");
    connect(checkButton, &QPushButton::clicked, this, &CrosswordWidget::checkAnswers);
    questionsLayout->addWidget(checkButton);
    
    QPushButton *backButton = new QPushButton("Назад к выбору уровня");
    connect(backButton, &QPushButton::clicked, this, [this]() { emit backToLevelSelect(); });
    questionsLayout->addWidget(backButton);
    
    scrollArea->setWidget(questionsWidget);
    scrollArea->setWidgetResizable(true);
    contentLayout->addWidget(scrollArea, 1);
    
    mainLayout->addLayout(contentLayout);
}

void CrosswordWidget::setCrossword(const Crossword &crossword) {
    currentCrossword = crossword;
    createGrid();
    createQuestionsList();
}

void CrosswordWidget::createGrid() {
    // Clear previous grid
    QLayoutItem *child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    cells.clear();

    int rows = currentCrossword.rows();
    int cols = currentCrossword.cols();

    cells.resize(rows);
    for (auto &row : cells) {
        row.resize(cols);
    }

    // Create grid cells
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QChar cell = currentCrossword.cellAt(row, col);
            if (cell != ' ') {
                QLineEdit *edit = new QLineEdit();
                edit->setMaxLength(1);
                edit->setAlignment(Qt::AlignCenter);
                edit->setValidator(new QRegularExpressionValidator(QRegularExpression("[А-Яа-я]"), this));
                edit->setStyleSheet("QLineEdit { font-size: 16px; }");
                
                gridLayout->addWidget(edit, row, col);
                cells[row][col] = edit;
            } else {
                QLabel *label = new QLabel();
                label->setStyleSheet("background-color: black;");
                gridLayout->addWidget(label, row, col);
                cells[row][col] = nullptr;
            }
        }
    }
}

void CrosswordWidget::createQuestionsList() {
    QString questionsText = "<h2>Вопросы:</h2><ol>";
    int questionNum = 1;
    
    for (const Question &q : currentCrossword.getQuestions()) {
        QString direction = q.isHorizontal ? "по горизонтали" : "по вертикали";
        questionsText += QString("<li>(%1,%2, %3) %4</li>")
                            .arg(q.position.x() + 1)
                            .arg(q.position.y() + 1)
                            .arg(direction)
                            .arg(q.text);
        questionNum++;
    }
    
    questionsText += "</ol>";
    questionsLabel->setText(questionsText);
}

void CrosswordWidget::checkAnswers() {
    int correct = 0;
    int total = 0;
    
    for (int row = 0; row < cells.size(); ++row) {
        for (int col = 0; col < cells[row].size(); ++col) {
            if (cells[row][col]) {
                total++;
                QString userAnswer = cells[row][col]->text().toUpper();
                QChar correctAnswer = currentCrossword.cellAt(row, col);
                
                if (userAnswer == correctAnswer) {
                    correct++;
                    cells[row][col]->setStyleSheet("background-color: lightgreen;");
                } else {
                    cells[row][col]->setStyleSheet("background-color: pink;");
                }
            }
        }
    }
    
    int percentage = total > 0 ? (correct * 100) / total : 0;
    QMessageBox::information(this, "Результат", 
        QString("Правильно: %1 из %2 (%3%)").arg(correct).arg(total).arg(percentage));
}
