#include <QApplication>
#include <QPushButton>
#include "app.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    App window;
    window.show();
    return QApplication::exec();
}
