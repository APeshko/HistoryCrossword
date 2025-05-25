#include "inputfieldfactory.h"
#include <QLineEdit>
#include <QRegularExpressionValidator>

QWidget* DefaultInputFieldFactory::createInputField(QWidget* parent) {
    QLineEdit* edit = new QLineEdit(parent);
    edit->setMaxLength(1);
    edit->setAlignment(Qt::AlignCenter);
    edit->setValidator(new QRegularExpressionValidator(QRegularExpression("[А-Яа-я]"), edit));
    edit->setStyleSheet("QLineEdit { font-size: 16px; }");
    return edit;
}
