#include <QApplication>
#include <QDebug>
#include "mainwindow.h"
#include "user.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QString config = "config.json";
    if (argc >= 2)
        config = argv[1];
    MainWindow window(nullptr, config);
    window.show();
    return app.exec();
}
