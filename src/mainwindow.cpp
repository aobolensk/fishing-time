#include "mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent, const QString &file) :
        QWidget(parent),
        grid(QGridLayout(this)),
        config_file(file),
        mainMenu(MainMenu(this, &grid)),
        loginMenu(LoginMenu(this, &grid)),
        gameMenu(GameMenu(this, &grid)),
        marketMenu(MarketMenu(this, &grid)),
        locations(Location::initializeLocations(this)) {
    this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    mainMenu.display();
    setLayout(&grid);
    grid.setColumnStretch(0, 1);
    grid.setColumnStretch(1, 1);
    grid.setColumnStretch(2, 1);
    deserialize();
    for (const User &user : users) {
        qDebug() << user.getUsername();
    }
}

void MainWindow::deserialize() {
    QFile config(config_file);
    if (!config.exists()) {
        qDebug() << "File " << config_file << " does not exist";
    } else if (!config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can not open file: " << config_file;
    } else {
        while (!config.atEnd()) {
            QVariant result;
            QByteArray data, s;
            while (!config.atEnd()) {
                s = config.readLine();
                data += s;
                if (s == "}\n")
                    break;
            }
            QJsonParseError jsonParseError;
            QVariantMap map = QJsonDocument::fromJson(data, &jsonParseError)
                    .object().toVariantMap();
            if (jsonParseError.error != QJsonParseError::NoError) {
                qDebug() << jsonParseError.errorString();
            }
            if (map["ftobj_type"] == QString("user")) {
                result = User::deserialize(map);
                if (!result.isNull()) {
                    users.push_back(result.value<User>());
                } else {
                    qDebug() << "Result of user deserialization is null";
                }
            }
        }
        config.close();
    }
}

void MainWindow::serialize() {
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

MainWindow::~MainWindow() {
    serialize();
}
