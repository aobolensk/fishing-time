#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        qDebug() << "Please, specify configuration file path";
        exit(1);
    }
    QApplication app(argc, argv);
    MainWindow window(nullptr, argv[1]);
    window.show();
    return app.exec();
}
