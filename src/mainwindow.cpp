#include "mainwindow.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    applyStyle();
    setWindowTitle("Исторический кроссворд");
    resize(800, 600);
}

void MainWindow::setupUI() {
    stackedWidget = new QStackedWidget(this);
    
    // Main screen
    mainScreen = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(mainScreen);
    
    QLabel *titleLabel = new QLabel("Исторический кроссворд");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    
    QPushButton *startButton = new QPushButton("Начать");
    connect(startButton, &QPushButton::clicked, this, &MainWindow::showLevelSelect);
    
    QPushButton *exitButton = new QPushButton("Выход");
    connect(exitButton, &QPushButton::clicked, this, &QMainWindow::close);
    
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(exitButton);
    mainLayout->addStretch();
    
    // Level select screen
    levelSelect = new LevelSelect();
    connect(levelSelect, &LevelSelect::levelSelected, this, &MainWindow::showCrossword);
    connect(levelSelect, &LevelSelect::backToMain, this, &MainWindow::showMainScreen);
    
    // Crossword screen
    crosswordWidget = new CrosswordWidget();
    connect(crosswordWidget, &CrosswordWidget::backToLevelSelect, this, &MainWindow::showLevelSelect);
    
    stackedWidget->addWidget(mainScreen);
    stackedWidget->addWidget(levelSelect);
    stackedWidget->addWidget(crosswordWidget);
    
    setCentralWidget(stackedWidget);
}

void MainWindow::applyStyle() {
    QFile styleFile(":/styles.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styleSheet = styleFile.readAll();
        setStyleSheet(styleSheet);
        styleFile.close();
    }
}

void MainWindow::showLevelSelect() {
    stackedWidget->setCurrentIndex(1);
}

void MainWindow::showCrossword(int level) {
    QString filePath = QString(":/data/level%1.json").arg(level);
    Crossword crossword;
    if (crossword.loadFromJson(filePath)) {
        crosswordWidget->setCrossword(crossword);
        stackedWidget->setCurrentIndex(2);
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить кроссворд");
    }
}

void MainWindow::showMainScreen() {
    stackedWidget->setCurrentIndex(0);
}
