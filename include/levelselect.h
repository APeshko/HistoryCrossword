#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>

class QPushButton;
class QVBoxLayout;

class LevelSelect : public QWidget {
    Q_OBJECT
public:
    explicit LevelSelect(QWidget *parent = nullptr);

signals:
    void levelSelected(int level);
    void backToMain();

private:
    void setupUI();

    QPushButton *level1Button;
    QPushButton *level2Button;
    QPushButton *level3Button;
    QPushButton *backButton;
    QVBoxLayout *layout;
};

#endif // LEVELSELECT_H
