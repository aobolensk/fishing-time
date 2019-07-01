#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "user.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    if (argc < 2) {
        MainWindow window(nullptr, "config.txt");
        window.show();
    } else {
        MainWindow window(nullptr, argv[1]);
        window.show();
    }
    return app.exec();
}
