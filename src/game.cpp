#include <QApplication>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMessageBox>
#include <QSettings>
#include "game.h"

Game::Game(QWidget *parent, const QString &file) :
        QWidget(parent),
        grid(QGridLayout(this)),
        configFile(file),
        #ifndef __MINGW32__
            randomGenerator(rd()),
        #else
            randomGenerator(static_cast<unsigned>(time(nullptr))),
        #endif  // __MINGW32__
        cfg(Config(this)),
        logger(Logger(this)),
        console(Console(this)),
        str(Dictionary(this)),
        locations(Location::initializeLocations()),
        mainMenu(MainMenu(this, &grid)),
        loginMenu(LoginMenu(this, &grid)),
        popUpInventoryMenu(PopUpInventoryMenu(this)),
        gameMenu(GameMenu(this, &grid, &popUpInventoryMenu)),
        marketMenu(MarketMenu(this, &grid)),
        storeMenu(StoreMenu(this, &grid)),
        settingsMenu(SettingsMenu(this, &grid)),
        netsMenu(NetsMenu(this, &grid)),
        statisticsMenu(StatisticsMenu(this, &grid)),
        itemStatisticsMenu(ItemStatisticsMenu(this, &grid)),
        signupMenu(SignupMenu(this, &grid)),
        usersettingsMenu(UsersettingsMenu(this, &grid)),
        ratingMenu(RatingMenu(this, &grid)),
        creditsMenu(CreditsMenu(this, &grid)),
        inventoryMenu(InventoryMenu(this, &grid)),
        locationMenu(LocationMenu(this, &grid)),
        userProfileMenu(UserProfileMenu(this, &grid)),
        aboutMenu(AboutMenu(this)) {
    QSettings settings;
    if (!this->restoreGeometry(settings.value("mainWindowGeometry").toByteArray())) {
        this->logger.error("Unable to restore game window geometry. Loading defaults...");
        this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    }
    this->setLayout(&grid);
    this->setWindowTitle(str.fishingTime);
    this->setWindowIcon(QIcon(Config::imagesDirectory + "icon.png"));
    grid.setColumnStretch(0, 1);
    grid.setColumnStretch(1, 1);
    grid.setColumnStretch(2, 1);
    this->deserialize();
    this->logger.setFile(this->logFile);
    this->mainMenu.display();
    this->logger.info("Logging system is successfully initialized!");
    this->logger.debug("Debug logging system is enabled!");
}

void Game::setAutoSavePeriod(int periodInMinutes) {
    disconnect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveFunction()));
    autoSaveTimer.stop();
    autoSavePeriod = periodInMinutes;
    autoSaveTimer.start(autoSavePeriod * 60 * 1000);
    connect(&autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSaveFunction()));
    this->logger.info("Autosave period is set to " + QString::number(autoSavePeriod) + " mins");
}

void Game::setConfigFile(const QString &newConfigFile) {
    this->configFile = newConfigFile;
    this->deserialize();
}

int Game::getAutoSavePeriod() {
    return autoSavePeriod;
}

void Game::resizeEvent(QResizeEvent *event) {
    (void) event;
    if (this->showBgImages && this->bgImagePath.size()) {
        QPixmap bkgnd(this->bgImagePath);
        int w = this->width();
        int h = this->height();
        bkgnd = bkgnd.scaled(QSize(w, h), Qt::KeepAspectRatio);
        if (this->height() > bkgnd.height()) {
            h = this->height();
            w = h * bkgnd.width() / bkgnd.height();
        } else {
            w = this->width();
            h = w * bkgnd.height() / bkgnd.width();
        }
        bkgnd = bkgnd.scaled(QSize(w, h), Qt::KeepAspectRatio);
        QPalette palette = this->palette();
        palette.setBrush(QPalette::Window, bkgnd);
        this->setPalette(palette);
    }
}

void Game::setBackgroundImage(const QString &backgroundImagePath) {
    if (this->showBgImages) {
        this->bgImagePath = backgroundImagePath;
        if (this->bgImagePath.size()) {
            QPixmap bkgnd(this->bgImagePath);
            int w = this->width();
            int h = this->height();
            bkgnd = bkgnd.scaled(QSize(w, h), Qt::KeepAspectRatio);
            if (this->height() > bkgnd.height()) {
                h = this->height();
                w = h * bkgnd.width() / bkgnd.height();
            } else {
                w = this->width();
                h = w * bkgnd.height() / bkgnd.width();
            }
            bkgnd = bkgnd.scaled(QSize(w, h), Qt::KeepAspectRatio);
            QPalette palette = this->palette();
            palette.setBrush(QPalette::Window, bkgnd);
            this->setPalette(palette);
        } else {
            QPalette palette = this->palette();
            switch (this->colorTheme) {
            case ColorTheme::LIGHT:
                palette.setColor(QPalette::Window, Config::LIGHT_THEME_WINDOW_COLOR);
                break;
            case ColorTheme::DARK:
                palette.setColor(QPalette::Window, Config::DARK_THEME_WINDOW_COLOR);
                break;
            }
            this->setPalette(palette);
        }
    }
}

void Game::deserialize() {
    this->users.clear();
    this->activeUser = -1;
    QFile config(configFile);
    if (!config.exists()) {
        this->logger.error("File " + configFile + " does not exist");
    } else if (!config.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->logger.error("Can not open file: " + configFile);
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
                    this->logger.error("Result of user deserialization is null");
                }
            } else if (map["fishingtime_object"] == QString("config")) {
                cfg.deserialize(map);
            } else {
                this->logger.error("Unknown object found in JSON file");
            }
        }
    }
    this->setFont(this->textFont);
    this->console.setFont(this->textFont);
    this->aboutMenu.setFont(this->textFont);
    this->gameMenu.getPopUpInventoryTable().setFont(this->textFont);
    str.setLanguage(activeLanguage);
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
    settings.setValue("loggerGeometry", logger.saveGeometry());
    settings.setValue("consoleGeometry", console.saveGeometry());
    settings.setValue("aboutWindowGeometry", aboutMenu.saveGeometry());
    settings.setValue("inventoryWindowGeometry", gameMenu.getPopUpInventoryTable().saveGeometry());
    updateTimePlayed();
    if (activeUser != -1 && activeLocation != -1)
        netsMenu.foldNets();
    QFile config(configFile);
    if (!config.open(QIODevice::WriteOnly | QIODevice::Text)) {
        this->logger.error("Can not open file: " + configFile);
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
    if (this->console.isHidden() && this->logger.isHidden()) {
        this->console.hide();
        this->logger.hide();
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

void Game::setCurrentMenu(Menu *menu) {
    this->currentMenu = menu;
}

Menu *Game::getCurrentMenu() const {
    return this->currentMenu;
}

void Game::autoSaveFunction() {
    this->logger.debug("Performing autosave");
    serialize();
    this->logger.debug("Autosave is complete");
}

QString Game::getConfigFileName() {
    return configFile;
}

void Game::manualSave() {
    serialize();
}

Game::~Game() {
    serialize();
}
