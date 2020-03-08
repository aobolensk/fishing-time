#include "testinventory.h"
#include "core.h"

void TestInventory::addNewItem() {
    Core core;
    core.users.push_back(User("user", "password"));
    core.users[0].inventory.changeItem("item.test", 10);
    QCOMPARE(core.users[0].inventory.getItem("item.test"), 10);
}

void TestInventory::getNonExistantItem() {
    Core core;
    core.users.push_back(User("user", "password"));
    QCOMPARE(core.users[0].inventory.getItem("item.test"), 0);
}

void TestInventory::deleteItem() {
    User user("username", "password");
    user.inventory.changeItem("test", 10);
    user.inventory.changeItem("test", -10);
    QCOMPARE(user.inventory.getItem("test"), 0);
}

void TestInventory::inventoryQuantityIsNotLessThanZero() {
    User user("username", "password");
    user.inventory.changeItem("test", 10);
    user.inventory.changeItem("test", -20);
    QCOMPARE(user.inventory.getItem("test"), 0);
}

void TestInventory::addNewStat() {
    User user("username", "password");
    user.inventory.changeItem("test", 10);
    user.inventory.updateStats("test", "received", 10, nullptr);
    QCOMPARE(user.inventory.getItemStats()["test"]["received"], 10);
}

void TestInventory::wrongStatIsEmpty() {
    User user("username", "password");
    user.inventory.changeItem("test", 10);
    user.inventory.updateStats("test", "received", 10, nullptr);
    QCOMPARE(user.inventory.getItemStats()["test"]["test2"], 0);
}

void TestInventory::wrongItemStatIsEmpty() {
    User user("username", "password");
    user.inventory.changeItem("test", 10);
    user.inventory.updateStats("test", "received", 10, nullptr);
    QCOMPARE(user.inventory.getItemStats()["test2"]["received"], 0);
}
