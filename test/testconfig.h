#ifndef TEST_TESTCONFIG_H_
#define TEST_TESTCONFIG_H_
#include <QtTest/QTest>

class TestConfig : public QObject {
    Q_OBJECT
private slots:
    void defaultConfigCheck();
    void reloadConfig();
    void defaultControlsAreSetAfterInitialization();
};

#endif  // TEST_TESTCONFIG_H_
