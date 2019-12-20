#include <QCryptographicHash>
#include "testuser.h"
#include "user.h"

void TestUser::getUsername() {
    User user("username", "password");
    QCOMPARE(user.getUsername(), QString("username"));
}

void TestUser::getPasswordHash() {
    User user("username", "password");
    QCOMPARE(user.getPasswordHash(), QString(QCryptographicHash::hash("password", QCryptographicHash::Md5)));
}

void TestUser::setPasswordHash() {
    User user("username", "password");
    user.setPasswordHash(QCryptographicHash::hash("new_password", QCryptographicHash::Md5));
    QCOMPARE(user.getPasswordHash(), QString(QCryptographicHash::hash("new_password", QCryptographicHash::Md5)));
}

void TestUser::getPrivilegeLevel() {
    User user("username", "password");
    QCOMPARE(user.getPrivilegeLevel(), 0);
}

void TestUser::setPrivilegeLevel() {
    User user("username", "password");
    user.setPrivilegeLevel(1);
    QCOMPARE(user.getPrivilegeLevel(), 1);
}

void TestUser::inventoryAddItem() {
    User user("username", "password");
    user.inventory.changeItem("test", 10);
    QCOMPARE(user.inventory.getItem("test"), 10);
}

void TestUser::inventoryDeleteItem() {
    User user("username", "password");
    user.inventory.changeItem("test", 10);
    user.inventory.changeItem("test", -10);
    QCOMPARE(user.inventory.getItem("test"), 0);
}

void TestUser::inventoryQuantityIsNotLessThanZero() {
    User user("username", "password");
    user.inventory.changeItem("test", 10);
    user.inventory.changeItem("test", -20);
    QCOMPARE(user.inventory.getItem("test"), 0);
}
