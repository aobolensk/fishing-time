#include "mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent, const QString &file) :
        QWidget(parent),
        grid(QGridLayout(this)),
        config_file(file),
        mainMenu(MainMenu(this, &grid)),
        loginMenu(LoginMenu(this, &grid)) {
    this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    mainMenu.display();
    setLayout(&grid);
    grid.setColumnStretch(0, 1);
    grid.setColumnStretch(1, 1);
    grid.setColumnStretch(2, 1);
    // Deserialization
    QFile config(config_file);
    if (!config.exists()) {
        qDebug() << "File " << config_file << " does not exist";
    } else if (!config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can not open file: " << config_file;
    } else {
        while (!config.atEnd()) {
            QVariant result;
            QByteArray arr, str;
            while (!config.atEnd()) {
                str = config.readLine();
                arr += str;
                if (str == "}\n")
                    break;
            }
            result = User::deserialize(arr);
            if (!result.isNull()) {
                users.push_back(result.value<User>());
            }
        }
        config.close();
    }
    for (const User &user : users) {
        qDebug() << user.getUsername();
    }
}

MainWindow::~MainWindow() {
    // Serialization
    QFile config(config_file);
    if (!config.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Can not open file: " << config_file;
    } else {
        for (const User &user : users) {
            config.write(user.serialize());
        }
        config.close();
    }
}
