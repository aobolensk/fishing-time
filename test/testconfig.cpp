#include "testconfig.h"
#include "core.h"

void TestConfig::defaultConfigCheck() {
    Core core;
    QJsonObject config = core.cfg.serialize();
    QCOMPARE(config["fishingtime_object"].toString(), QStringLiteral("config"));
    QCOMPARE(config["autoSavePeriod"].toInt(), 3);
    QCOMPARE(config["colorTheme"].toInt(), 0);
    QCOMPARE(config["inventoryType"].toInt(), 0);
    QCOMPARE(config["language"].toInt(), 0);
    QCOMPARE(config["loggerLevel"].toInt(), 0);
    QCOMPARE(config["showBgImages"].toInt(), 1);
    QCOMPARE(config["logFile"].toString(), QStringLiteral("log.txt"));
}

void TestConfig::reloadConfig() {
    Core core;
    QJsonObject config = core.cfg.serialize();
    core.cfg.deserialize(config.toVariantMap());
    config = core.cfg.serialize();
    QCOMPARE(config["fishingtime_object"].toString(), QStringLiteral("config"));
    QCOMPARE(config["autoSavePeriod"].toInt(), 3);
    QCOMPARE(config["colorTheme"].toInt(), 0);
    QCOMPARE(config["inventoryType"].toInt(), 0);
    QCOMPARE(config["language"].toInt(), 0);
    QCOMPARE(config["loggerLevel"].toInt(), 0);
    QCOMPARE(config["showBgImages"].toInt(), 1);
    QCOMPARE(config["logFile"].toString(), QStringLiteral("log.txt"));
}

void TestConfig::defaultControlsAreSetAfterInitialization() {
    Core core;
    QJsonObject config = core.cfg.serialize();
    for (size_t i = 0; i < static_cast<size_t>(Controls::CONTROLS_N); ++i) {
        QCOMPARE(core.cfg.getKey(static_cast<Controls>(i)), core.cfg.defaultControls[i]);
    }
}
