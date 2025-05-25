#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "levelselect.h"
#include "crosswordwidget.h"

class QStackedWidget;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void showLevelSelect();
    void showCrossword(int level);
    void showMainScreen();

private:
    void setupUI();
    void applyStyle();

    QStackedWidget *stackedWidget;
    LevelSelect *levelSelect;
    CrosswordWidget *crosswordWidget;
    QWidget *mainScreen;
};

#endif // MAINWINDOW_H
