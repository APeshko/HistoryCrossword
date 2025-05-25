#include "crosswordwidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

CrosswordWidget::CrosswordWidget(ICrossword* crossword,
                               IAnswerChecker* answerChecker,
                               IInputFieldFactory* fieldFactory,
                               QWidget* parent)
    : QWidget(parent), m_crossword(crossword),
      m_answerChecker(answerChecker), m_fieldFactory(fieldFactory) {
    setupUI();
    if (m_crossword) {
        createGrid();
        createQuestionsList();
    }
}

void CrosswordWidget::setCrossword(ICrossword* crossword) {
    m_crossword = crossword;
    createGrid();
    createQuestionsList();
}

void CrosswordWidget::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QLabel* titleLabel = new QLabel(this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    mainLayout->addWidget(titleLabel);

    QHBoxLayout* contentLayout = new QHBoxLayout();
    
    QWidget* gridWidget = new QWidget();
    m_gridLayout = new QGridLayout(gridWidget);
    m_gridLayout->setSpacing(2);
    contentLayout->addWidget(gridWidget, 3);
    
    QScrollArea* scrollArea = new QScrollArea();
    QWidget* questionsWidget = new QWidget();
    QVBoxLayout* questionsLayout = new QVBoxLayout(questionsWidget);
    
    m_questionsLabel = new QLabel();
    m_questionsLabel->setWordWrap(true);
    questionsLayout->addWidget(m_questionsLabel);
    
    QPushButton* checkButton = new QPushButton("Проверить ответы");
    connect(checkButton, &QPushButton::clicked, this, &CrosswordWidget::checkAnswers);
    questionsLayout->addWidget(checkButton);
    
    QPushButton* backButton = new QPushButton("Назад к выбору уровня");
    connect(backButton, &QPushButton::clicked, this, [this]() { emit backToLevelSelect(); });
    questionsLayout->addWidget(backButton);
    
    scrollArea->setWidget(questionsWidget);
    scrollArea->setWidgetResizable(true);
    contentLayout->addWidget(scrollArea, 1);
    
    mainLayout->addLayout(contentLayout);
}

void CrosswordWidget::createGrid() {
    // Clear previous grid
    QLayoutItem* child;
    while ((child = m_gridLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    m_cells.clear();

    if (!m_crossword) return;

    int rows = m_crossword->rows();
    int cols = m_crossword->cols();

    m_cells.resize(rows);
    for (auto& row : m_cells) {
        row.resize(cols);
    }

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            QChar cell = m_crossword->cellAt(row, col);
            if (cell != ' ') {
                QWidget* inputField = m_fieldFactory->createInputField(this);
                m_gridLayout->addWidget(inputField, row, col);
                m_cells[row][col] = inputField;
            } else {
                QLabel* label = new QLabel(this);
                label->setStyleSheet("background-color: black;");
                m_gridLayout->addWidget(label, row, col);
                m_cells[row][col] = nullptr;
            }
        }
    }
}

void CrosswordWidget::checkAnswers() {
    if (m_answerChecker && m_crossword) {
        m_answerChecker->checkAnswers(m_cells, m_crossword);
    }
}
