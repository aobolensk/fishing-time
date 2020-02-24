#include <QApplication>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonParseError>
#include <QMessageBox>
#include <QSettings>
#include "game.h"
#include "utils.h"

Game::Game(QWidget *parent, const QString &file) :
        QWidget(parent),
        grid(QGridLayout(this)),
        configFile(file),
        core(),
        randomGenerator(core.randomGenerator),
        cfg(core.cfg),
        str(core.str),
        users(core.users),
        locations(core.locations),
        activeUser(core.activeUser),
        activeLocation(core.activeLocation),
        activeLanguage(core.activeLanguage),
        bgImagePath(core.bgImagePath),
        showBgImages(core.showBgImages),
        userTimestamp(core.userTimestamp),
        inventoryType(core.inventoryType),
        colorTheme(core.colorTheme),
        loggerLevel(core.loggerLevel),
        textFont(core.textFont),
        logFile(core.logFile),
        autoSavePeriod(core.autoSavePeriod),
        logger(Logger(this)),
        console(Console(this)),
        mainMenu(MainMenu(this, &grid)),
        loginMenu(LoginMenu(this, &grid)),
        popUpInventoryMenu(InventoryMenu(this, nullptr, true)),
        gameMenu(GameMenu(this, &grid, &popUpInventoryMenu)),
        marketMenu(MarketMenu(this, &grid)),
        lotteryMenu(LotteryMenu(this, &grid)),
        storeMenu(StoreMenu(this, &grid)),
        settingsMenu(SettingsMenu(this, &grid)),
        appearanceSettingsMenu(AppearanceSettingsMenu(this, &grid)),
        controlsMenu(ControlsMenu(this, &grid)),
        netsMenu(NetsMenu(this, &grid)),
        statisticsMenu(StatisticsMenu(this, &grid)),
        itemStatisticsMenu(ItemStatisticsMenu(this, &grid)),
        coinStatisticsMenu(CoinStatisticsMenu(this, &grid)),
        signupMenu(SignupMenu(this, &grid)),
        usersettingsMenu(UsersettingsMenu(this, &grid)),
        ratingMenu(RatingMenu(this, &grid)),
        creditsMenu(CreditsMenu(this, &grid)),
        inventoryMenu(InventoryMenu(this, &grid, false)),
        locationMenu(LocationMenu(this, &grid)),
        userProfileMenu(UserProfileMenu(this, &grid)),
        aboutMenu(AboutMenu(this)),
        overlay(OverlayWidget(this)) {
    Q_INIT_RESOURCE(resources);
    QSettings settings;
    if (!this->restoreGeometry(settings.value("mainWindowGeometry").toByteArray())) {
        this->logger.error("Unable to restore game window geometry. Loading defaults...");
        this->setGeometry(QRect(QPoint(100, 100), QSize(640, 480)));
    }
    this->setLayout(&grid);
    this->setWindowTitle(core.str.fishingTime);
    this->setWindowIcon(QIcon(":/images/icon.png"));
    grid.setColumnStretch(0, 1);
    grid.setColumnStretch(1, 1);
    grid.setColumnStretch(2, 1);
    this->deserialize();
    this->logger.setFile(core.logFile);
    this->mainMenu.display();
    this->logger.info("Logging system is successfully initialized!");
    this->logger.debug("Debug logging system is enabled!");
    overlay.setText(core.str.debugOverlayText.arg(
        TOSTRING(COMMIT_HASH),
        this->aboutMenu.getSystemInfo()
    ));
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
    return core.autoSavePeriod;
}

void Game::resizeEvent(QResizeEvent *event) {
    (void) event;
    if (core.showBgImages && core.bgImagePath.size()) {
        QPixmap bkgnd(core.bgImagePath);
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
    if (core.showBgImages) {
        core.bgImagePath = backgroundImagePath;
        if (core.bgImagePath.size()) {
            QPixmap bkgnd(core.bgImagePath);
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
            switch (core.colorTheme) {
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
    core.users.clear();
    core.activeUser = -1;
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
                    core.users.push_back(result.value<User>());
                } else {
                    this->logger.error("Result of user deserialization is null");
                }
            } else if (map["fishingtime_object"] == QString("config")) {
                core.cfg.deserialize(this, map);
            } else {
                this->logger.error("Unknown object found in JSON file");
            }
        }
    }
    this->setFont(core.textFont);
    this->console.setFont(core.textFont);
    this->aboutMenu.setFont(core.textFont);
    this->gameMenu.getPopUpInventoryTable().setFont(core.textFont);
    this->controlsMenu.setDefaults();
    core.str.setLanguage(core.activeLanguage);
    setAutoSavePeriod(core.autoSavePeriod);
    core.cfg.applyColorTheme(this, core.colorTheme);
}

void Game::hideAll() {
    this->hide();
    this->console.hide();
    this->logger.hide();
    this->aboutMenu.hide();
    this->popUpInventoryMenu.hide();
}

void Game::updateTimePlayed() {
    if (core.activeUser != -1 && core.userTimestamp.isValid()) {
        core.users[core.activeUser].incInGameTime(
            QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000 -
            core.userTimestamp.toMSecsSinceEpoch() / 1000
        );
        core.userTimestamp = QDateTime::currentDateTime();
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
    if (core.activeUser != -1 && core.activeLocation != -1)
        netsMenu.foldNets();
    QFile config(configFile);
    if (!config.open(QIODevice::WriteOnly | QIODevice::Text)) {
        this->logger.error("Can not open file: " + configFile);
    } else {
        QJsonArray jsons;
        jsons.push_back(core.cfg.serialize(this));
        for (const User &user : core.users) {
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
            QMessageBox::question(this, core.str.fishingTime, core.str.exitConfirmation,
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
