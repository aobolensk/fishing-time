#include "user.h"

void User::Inventory::changeItem(const QString &name, int quantity) {
    if (true) {
        QMap <QString, int>::iterator it = inventory.find(name);
        if (it == inventory.end()) {
            if (quantity <= 0)
                return;
            inventory.insert(name, quantity);
        } else {
            it.value() += quantity;
            if (it.value() <= 0)
                inventory.erase(it);
        }
    }
    if (quantity > 0) {
        QMap <QString, QMap <QString, int>>::iterator it = itemStatistics.find(name);
        if (it == itemStatistics.end()) {
            QMap <QString, int> statistics;
            statistics["stats.got"] = quantity;
            itemStatistics.insert(name, statistics);
        } else {
            it.value()["stats.got"] += quantity;
        }
    }
}

void User::Inventory::updateStats(const QString &name, const QString &stat, int quantity) {
    Q_ASSERT(quantity >= 0);
    auto it = itemStatistics.find(name);
    if (it == itemStatistics.end()) {
        return;
    }
    it.value()[stat] += quantity;
}

int User::Inventory::getItem(const QString &name) {
    QMap <QString, int>::iterator it = inventory.find(name);
    if (it != inventory.end())
        return it.value();
    return 0;
}

const QMap <QString, int> &User::Inventory::get() const {
    return inventory;
}

const QMap <QString, QMap <QString, int>> &User::Inventory::getItemStats() const {
    return itemStatistics;
}

QMap <QString, int> &User::Inventory::set() {
    return inventory;
}

QMap <QString, QMap <QString, int>> &User::Inventory::setItemStats() {
    return itemStatistics;
}
