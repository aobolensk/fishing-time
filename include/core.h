#ifndef INCLUDE_CORE_H_
#define INCLUDE_CORE_H_
#include <QDateTime>
#include <QString>
#include <random>
#include "config.h"
#include "dictionary.h"
#include "user.h"
#include "location.h"

class Core {
private:
    std::random_device rd;
public:
    std::mt19937 randomGenerator;
    Config cfg;
    Dictionary str;
    QVector <User> users;
    QVector <Location> locations;
    int activeUser = -1;
    int activeLocation = -1;
    Language activeLanguage = Language::English;
    QString bgImagePath;
    bool showBgImages = true;
    QDateTime userTimestamp;
    InventoryType inventoryType = InventoryType::POPUP;
    ColorTheme colorTheme = ColorTheme::LIGHT;
    LoggerLevel loggerLevel = LoggerLevel::RELEASE;
    QFont textFont = QFont("Noto Sans", 11, QFont::Normal, false);
    QString logFile = "log.txt";
    int autoSavePeriod = 3;
    void setAutoSavePeriod(int periodInMinutes);
public:
    Core();
};

#endif // INCLUDE_CORE_H_
