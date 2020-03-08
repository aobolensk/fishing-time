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
