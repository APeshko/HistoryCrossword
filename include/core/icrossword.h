#ifndef ICROSSWORD_H
#define ICROSSWORD_H

#include "question.h"
#include <vector>

class ICrossword {
public:
    virtual ~ICrossword() = default;
    virtual const std::vector<Question>& getQuestions() const = 0;
    virtual QChar cellAt(int row, int col) const = 0;
    virtual int rows() const = 0;
    virtual int cols() const = 0;
    virtual QString title() const = 0;
};

#endif // ICROSSWORD_H
