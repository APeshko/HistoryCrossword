#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QPoint>

struct Question {
    QString text;
    QString answer;
    QPoint position;
    bool isHorizontal;
};

#endif // QUESTION_H
