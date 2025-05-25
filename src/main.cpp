#include "ui/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    //QFont defaultFont("Arial", 12);
    //app.setFont(defaultFont)
    MainWindow w;
    w.show();
    return a.exec();
}
