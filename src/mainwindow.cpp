#include "mainwindow.h"
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent, const QString &file) :
        QWidget(parent),
        grid(QGridLayout(this)),
        config_file(file),
        cfg(Config(this)),
        locations(Location::initializeLocations(this)),
        mainMenu(MainMenu(this, &grid)),
        loginMenu(LoginMenu(this, &grid)),
        gameMenu(GameMenu(this, &grid)),
        marketMenu(MarketMenu(this, &grid)),
        storeMenu(StoreMenu(this, &grid)),
        settingsMenu(SettingsMenu(this, &grid)) {
    this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    setLayout(&grid);
    grid.setColumnStretch(0, 1);
    grid.setColumnStretch(1, 1);
    grid.setColumnStretch(2, 1);
    deserialize();
    str.setLanguage(activeLanguage);
    qDebug() << "lang:" << (int)activeLanguage;
    for (const User &user : users) {
        qDebug() << user.getUsername();
    }
    mainMenu.display();
    setAutoSavePeriod(3);
}

void MainWindow::setAutoSavePeriod(int periodInMinutes) {
    disconnect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveFunction()));
    autoSaveTimer.stop();
    autoSaveTimer.start(periodInMinutes * 60 * 1000);
    connect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveFunction()));
    qDebug() << "Autosave period is set to " << periodInMinutes << " mins";
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
            QByteArray jsonStr, s;
            while (!config.atEnd()) {
                s = config.readLine();
                jsonStr += s;
                if (s == "}\n")
                    break;
            }
            QJsonParseError jsonParseError;
            QVariantMap map = QJsonDocument::fromJson(jsonStr, &jsonParseError)
                    .object().toVariantMap();
            if (jsonParseError.error != QJsonParseError::NoError) {
                qDebug() << jsonParseError.errorString();
            }
            if (map["fishingtime_object"] == QString("user")) {
                result = User::deserialize(map);
                if (!result.isNull()) {
                    users.push_back(result.value<User>());
                } else {
                    qDebug() << "Result of user deserialization is null";
                }
            } else if (map["fishingtime_object"] == QString("config")) {
                cfg.deserialize(map);
            } else {
                qDebug() << "Unknown object found in JSON file";
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
        config.write(cfg.serialize());
        for (const User &user : users) {
            config.write(user.serialize());
        }
        config.close();
    }
}

void MainWindow::autoSaveFunction() {
    qDebug() << "Performing autosave";
    serialize();
    qDebug() << "Autosave is complete";
}

MainWindow::~MainWindow() {
    serialize();
}
