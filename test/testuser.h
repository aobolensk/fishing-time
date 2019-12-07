#ifndef TEST_TESTUSER_H_
#define TEST_TESTUSER_H_
#include <QtTest/QTest>

class TestUser : public QObject {
    Q_OBJECT
private slots:
    void getUsername();
    void getPasswordHash();
    void setPasswordHash();
    void getPrivilegeLevel();
    void setPrivilegeLevel();
};

#endif  // TEST_TESTUSER_H_
