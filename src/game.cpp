#include <QApplication>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMessageBox>
#include <QSettings>
#include "game.h"

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
        str(Dictionary(this)),
        locations(Location::initializeLocations()),
        mainMenu(MainMenu(this, &grid)),
        loginMenu(LoginMenu(this, &grid)),
        gameMenu(GameMenu(this, &grid)),
        marketMenu(MarketMenu(this, &grid)),
        storeMenu(StoreMenu(this, &grid)),
        settingsMenu(SettingsMenu(this, &grid)),
        netsMenu(NetsMenu(this, &grid)),
        statisticsMenu(StatisticsMenu(this, &grid)),
        itemStatisticsMenu(ItemStatisticsMenu(this, &grid)),
        signupMenu(SignupMenu(this, &grid)),
        usersettingsMenu(UsersettingsMenu(this, &grid)),
        ratingMenu(RatingMenu(this, &grid)),
        inventoryMenu(InventoryMenu(this, &grid)),
        locationMenu(LocationMenu(this, &grid)),
        aboutMenu(AboutMenu(this)) {
    QSettings settings;
    if (!this->restoreGeometry(settings.value("mainWindowGeometry").toByteArray())) {
        qDebug() << "Unable to restore game window geometry. Loading defaults...";
        this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    }
    this->setLayout(&grid);
    this->setWindowTitle(str.fishingTime);
    grid.setColumnStretch(0, 1);
    grid.setColumnStretch(1, 1);
    grid.setColumnStretch(2, 1);
    this->deserialize();
    this->mainMenu.display();
}

void Game::setAutoSavePeriod(int periodInMinutes) {
    disconnect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveFunction()));
    autoSaveTimer.stop();
    autoSavePeriod = periodInMinutes;
    autoSaveTimer.start(autoSavePeriod * 60 * 1000);
    connect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveFunction()));
    qDebug() << "Autosave period is set to " << autoSavePeriod << " mins";
}

void Game::setConfigFile(const QString &new_config_file) {
    this->config_file = new_config_file;
    this->deserialize();
}

int Game::getAutoSavePeriod() {
    return autoSavePeriod;
}

void Game::deserialize() {
    this->users.clear();
    this->activeUser = -1;
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
    this->setFont(this->textFont);
    this->console.setFont(this->textFont);
    this->aboutMenu.setFont(this->textFont);
    this->gameMenu.getPopUpInventoryTable().setFont(this->textFont);
    str.setLanguage(activeLanguage);
    for (const User &user : users) {
        qDebug() << user.getUsername();
    }
    setAutoSavePeriod(autoSavePeriod);
    this->cfg.applyColorTheme(colorTheme);
}

void Game::updateTimePlayed() {
    if (activeUser != -1 && userTimestamp.isValid()) {
        this->users[this->activeUser].incInGameTime(
            QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000 -
            userTimestamp.toMSecsSinceEpoch() / 1000
        );
        userTimestamp = QDateTime::currentDateTime();
    }
}

void Game::serialize() {
    QSettings settings;
    settings.setValue("mainWindowGeometry", this->saveGeometry());
    settings.setValue("consoleGeometry", console.saveGeometry());
    settings.setValue("aboutWindowGeometry", aboutMenu.saveGeometry());
    settings.setValue("inventoryWindowGeometry", gameMenu.getPopUpInventoryTable().saveGeometry());
    updateTimePlayed();
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
    if (!this->console.isDisplayed()) {
        QMessageBox::StandardButton closeResult =
            QMessageBox::question(this, str.fishingTime, str.exitConfirmation,
            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
        if (closeResult != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
            QApplication::quit();
        }
    } else {
        this->hide();
    }
}

void Game::hideCurrentMenu() {
    if (mainMenu.isDisplayed()) {
        mainMenu.hide();
    } else if (loginMenu.isDisplayed()) {
        loginMenu.hide();
    } else if (gameMenu.isDisplayed()) {
        gameMenu.hide();
    } else if (marketMenu.isDisplayed()) {
        marketMenu.hide();
    } else if (storeMenu.isDisplayed()) {
        storeMenu.hide();
    } else if (settingsMenu.isDisplayed()) {
        settingsMenu.hide();
    } else if (netsMenu.isDisplayed()) {
        netsMenu.hide();
    } else if (statisticsMenu.isDisplayed()) {
        statisticsMenu.hide();
    } else if (signupMenu.isDisplayed()) {
        signupMenu.hide();
    } else if (usersettingsMenu.isDisplayed()) {
        usersettingsMenu.hide();
    } else if (ratingMenu.isDisplayed()) {
        ratingMenu.hide();
    } else if (inventoryMenu.isDisplayed()) {
        inventoryMenu.hide();
    }
}

void Game::autoSaveFunction() {
    qDebug() << "Performing autosave";
    serialize();
    qDebug() << "Autosave is complete";
}

QString Game::getConfigFileName() {
    return config_file;
}

void Game::manualSave() {
    serialize();
}

Game::~Game() {
    serialize();
}
