#include "game.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonParseError>

Game::Game(QWidget *parent, const QString &file) :
        QWidget(parent),
        grid(QGridLayout(this)),
        config_file(file),
        #ifndef __MINGW32__
            randomGenerator(rd()),
        #else
            randomGenerator(static_cast<unsigned>(time(nullptr))),
        #endif  // __MINGW32__
        cfg(Config(this)),
        console(Console(this)),
        locations(Location::initializeLocations(this)),
        mainMenu(MainMenu(this, &grid)),
        loginMenu(LoginMenu(this, &grid)),
        gameMenu(GameMenu(this, &grid)),
        marketMenu(MarketMenu(this, &grid)),
        storeMenu(StoreMenu(this, &grid)),
        settingsMenu(SettingsMenu(this, &grid)),
        netsMenu(NetsMenu(this, &grid)),
        statisticsMenu(StatisticsMenu(this, &grid)),
        signupMenu(SignupMenu(this, &grid)),
        usersettingsMenu(UsersettingsMenu(this, &grid)),
        ratingMenu(RatingMenu(this, &grid)) {
    this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    this->setLayout(&grid);
    this->setWindowTitle(str.fishingTime);
    grid.setColumnStretch(0, 1);
    grid.setColumnStretch(1, 1);
    grid.setColumnStretch(2, 1);
    deserialize();
    str.setLanguage(activeLanguage);
    for (const User &user : users) {
        qDebug() << user.getUsername();
    }
    mainMenu.display();
    setAutoSavePeriod(autoSavePeriod);
}

void Game::setAutoSavePeriod(int periodInMinutes) {
    disconnect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveFunction()));
    autoSaveTimer.stop();
    autoSavePeriod = periodInMinutes;
    autoSaveTimer.start(autoSavePeriod * 60 * 1000);
    connect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveFunction()));
    qDebug() << "Autosave period is set to " << autoSavePeriod << " mins";
}

void Game::deserialize() {
    QFile config(config_file);
    if (!config.exists()) {
        qDebug() << "File " << config_file << " does not exist";
    } else if (!config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can not open file: " << config_file;
    } else {
        QVariant result;
        QString jsons = config.readAll();
        config.close();
        QJsonArray arr = QJsonDocument::fromJson(jsons.toUtf8()).array();
        for (int i = 0; i < arr.count(); ++i) {
            QVariantMap map = arr[i].toObject().toVariantMap();
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
    }
}

void Game::serialize() {
    if (activeUser != -1 && activeLocation != -1)
        netsMenu.foldNets();
    QFile config(config_file);
    if (!config.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Can not open file: " << config_file;
    } else {
        QJsonArray jsons;
        jsons.push_back(cfg.serialize());
        for (const User &user : users) {
            jsons.push_back(user.serialize());
        }
        QJsonDocument doc(jsons);
        config.write(doc.toJson());
        config.close();
    }
}

void Game::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton closeResult =
        QMessageBox::question(this, str.fishingTime, str.exitConfirmation,
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
    if (closeResult != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        QApplication::quit();
    }
}

void Game::autoSaveFunction() {
    qDebug() << "Performing autosave";
    serialize();
    qDebug() << "Autosave is complete";
}

Game::~Game() {
    serialize();
}
