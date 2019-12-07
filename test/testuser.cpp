#include <QCryptographicHash>
#include "testuser.h"
#include "user.h"

void TestUser::getUsername() {
    User user("username", "password");
    QCOMPARE(user.getUsername(), QString("username"));
}

void TestUser::getPasswordHash() {
    User user("username", "password");
    QCOMPARE(user.getPasswordHash(), QCryptographicHash::hash("password", QCryptographicHash::Md5));
}

void TestUser::setPasswordHash() {
    User user("username", "password");
    user.setPasswordHash(QCryptographicHash::hash("new_password", QCryptographicHash::Md5));
    QCOMPARE(user.getPasswordHash(), QCryptographicHash::hash("new_password", QCryptographicHash::Md5));
}
