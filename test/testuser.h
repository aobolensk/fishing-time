#ifndef TEST_TESTUSER_H_
#define TEST_TESTUSER_H_
#include <QtTest/QTest>

class TestUser : public QObject {
    Q_OBJECT
private slots:
    void getUsername();
};

#endif  // TEST_TESTUSER_H_
