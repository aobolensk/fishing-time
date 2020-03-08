#include "testconfig.h"
#include "core.h"

void TestConfig::defaultConfigCheck() {
    Core core;
    QJsonObject jsonObj = core.cfg.serialize();
    QCOMPARE(jsonObj["fishingtime_object"].toString(), "config");
    QCOMPARE(jsonObj["autoSavePeriod"].toInt(), 3);
    QCOMPARE(jsonObj["colorTheme"].toInt(), 0);
    QCOMPARE(jsonObj["inventoryType"].toInt(), 0);
    QCOMPARE(jsonObj["language"].toInt(), 0);
    QCOMPARE(jsonObj["loggerLevel"].toInt(), 0);
    QCOMPARE(jsonObj["showBgImages"].toInt(), 1);
    QCOMPARE(jsonObj["logFile"].toString(), "log.txt");
}
