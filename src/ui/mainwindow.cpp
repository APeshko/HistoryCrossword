#include "mainwindow.h"
#include "ui/levelselect.h"
#include "ui/crosswordwidget.h"
#include "data/jsoncrosswordloader.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. Настройка основного окна
    setWindowTitle("Исторический кроссворд");
    resize(800, 600);

    // 2. Создание виджетов
    setupUi();
    applyStyles();

    // 3. Подключение сигналов
    connectSignals();
}

void MainWindow::setupUi()
{
    // Главный контейнер для переключения экранов
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    // 1. Экран главного меню
    QWidget *mainScreen = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout(mainScreen);
    
    QLabel *titleLabel = new QLabel("Исторический кроссворд");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    
    QPushButton *startButton = new QPushButton("Начать");
    QPushButton *exitButton = new QPushButton("Выход");
    
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(exitButton);
    mainLayout->addStretch();

    // 2. Экран выбора уровня
    levelSelect = new LevelSelect();

    // 3. Экран кроссворда (пока пустой, будет создаваться динамически)
    crosswordWidget = nullptr;

    // Добавляем экраны в стек
    stackedWidget->addWidget(mainScreen);
    stackedWidget->addWidget(levelSelect);
}

void MainWindow::connectSignals()
{
    // Кнопка "Начать" → переход к выбору уровня
    QPushButton *startBtn = findChild<QPushButton*>();
    connect(startBtn, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(1); // Индекс экрана выбора уровня
    });

    // Кнопка "Выход" → закрытие приложения
    QPushButton *exitBtn = findChild<QPushButton*>(QString(), Qt::FindDirectChildrenOnly);
    connect(exitBtn, &QPushButton::clicked, this, &QMainWindow::close);

    // Сигналы от экрана выбора уровня
    connect(levelSelect, &LevelSelect::levelSelected, this, &MainWindow::loadCrossword);
    connect(levelSelect, &LevelSelect::backToMain, this, &MainWindow::showMainScreen);
}

void MainWindow::applyStyles()
{
    // Загрузка стилей из файла
    QFile styleFile(":/styles.qss");
    if (styleFile.open(QIODevice::ReadOnly)) {
        QString styleSheet = styleFile.readAll();
        setStyleSheet(styleSheet);
    }
}

void MainWindow::loadCrossword(int level)
{
    // 1. Загрузка данных
    JsonCrosswordLoader loader;
    QString filePath = QString(":/data/level%1.json").arg(level);
    ICrossword *crossword = loader.load(filePath);

    if (!crossword) {
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить кроссворд");
        return;
    }

    // 2. Удаляем предыдущий виджет кроссворда (если был)
    if (stackedWidget->count() > 2) {
        QWidget *oldWidget = stackedWidget->widget(2);
        stackedWidget->removeWidget(oldWidget);
        delete oldWidget;
    }

    // 3. Создаем новый виджет
    crosswordWidget = new CrosswordWidget(
        crossword,
        new BasicAnswerChecker(),
        new DefaultInputFieldFactory()
    );

    // 4. Подключаем сигналы
    connect(crosswordWidget, &CrosswordWidget::backToLevelSelect, this, [this]() {
        stackedWidget->setCurrentIndex(1); // Возврат к выбору уровня
    });

    // 5. Добавляем в стек и переключаемся
    stackedWidget->addWidget(crosswordWidget);
    stackedWidget->setCurrentIndex(2);
}

void MainWindow::showMainScreen()
{
    stackedWidget->setCurrentIndex(0); // Индекс главного экрана
}
