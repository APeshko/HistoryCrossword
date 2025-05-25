#ifndef INPUTFIELDFACTORY_H
#define INPUTFIELDFACTORY_H

#include <QWidget>

class IInputFieldFactory {
public:
    virtual ~IInputFieldFactory() = default;
    virtual QWidget* createInputField(QWidget* parent = nullptr) = 0;
};

class DefaultInputFieldFactory : public IInputFieldFactory {
public:
    QWidget* createInputField(QWidget* parent = nullptr) override;
};

#endif // INPUTFIELDFACTORY_H
