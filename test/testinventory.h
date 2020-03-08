#ifndef TEST_TESTINVENTORY_H_
#define TEST_TESTINVENTORY_H_
#include <QtTest/QTest>

class TestInventory : public QObject {
    Q_OBJECT
private slots:
    void addNewItem();
    void getNonExistantItem();
    void deleteItem();
    void inventoryQuantityIsNotLessThanZero();
    void addNewStat();
    void wrongStatIsEmpty();
    void wrongItemStatIsEmpty();
};

#endif  // TEST_TESTINVENTORY_H_
