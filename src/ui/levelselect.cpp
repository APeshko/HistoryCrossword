#include "levelselect.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

LevelSelect::LevelSelect(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void LevelSelect::setupUI() {
    layout = new QVBoxLayout(this);
    
    QLabel *titleLabel = new QLabel("Выберите уровень сложности");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    layout->addWidget(titleLabel);
    
    level1Button = new QPushButton("Уровень 1: Легкий");
    level2Button = new QPushButton("Уровень 2: Средний");
    level3Button = new QPushButton("Уровень 3: Сложный");
    backButton = new QPushButton("Назад");
    
    connect(level1Button, &QPushButton::clicked, this, [this]() { emit levelSelected(1); });
    connect(level2Button, &QPushButton::clicked, this, [this]() { emit levelSelected(2); });
    connect(level3Button, &QPushButton::clicked, this, [this]() { emit levelSelected(3); });
    connect(backButton, &QPushButton::clicked, this, &LevelSelect::backToMain);
    
    layout->addWidget(level1Button);
    layout->addWidget(level2Button);
    layout->addWidget(level3Button);
    layout->addStretch();
    layout->addWidget(backButton);
    
    setLayout(layout);
}
