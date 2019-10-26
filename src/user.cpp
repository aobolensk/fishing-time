#include <QTemporaryFile>
#include <QDataStream>
#include <QDateTime>
#include "game.h"
#include "user.h"
#include "serialization.h"

User::User(const QString &name, const QString &password) :
    username(name),
    passwordHash(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5)),
    signUpTime(QDateTime::currentDateTime().toString(Qt::ISODate)) {
    
}

QJsonObject User::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "user";
    jsonObj["username"] = username;
    jsonObj["clicks"] = clicks;
    jsonObj["coins"] = coins;
    jsonObj["privilegeLevel"] = privilegeLevel;
    jsonObj["passwordHash"] = passwordHash;
    jsonObj["signUpTime"] = signUpTime;
    jsonObj["inGameTime"] = inGameTime;
    QVariantMap inv;
    for (auto i = inventory.get().begin(); i != inventory.get().end(); ++i) {
        inv[i.key()] = i.value();
    }
    jsonObj["inventory"] = QJsonObject::fromVariantMap(inv);
    QVariantMap itemStats;
    for (auto i = inventory.getItemStats().begin(); i != inventory.getItemStats().end(); ++i) {
        QVariantMap stat;
        for (auto j = i.value().begin(); j != i.value().end(); ++j) {
            stat[j.key()] = j.value();
        }
        itemStats[i.key()].setValue(stat);
    }
    jsonObj["itemStats"] = QJsonObject::fromVariantMap(itemStats);
    return jsonObj;
}

QVariant User::deserialize(const QVariantMap &map) {
    User user = User(map["username"].toString());
    user.clicks = map["clicks"].toLongLong();
    user.coins = map["coins"].toLongLong();
    user.privilegeLevel = map["privilegeLevel"].toInt();
    user.passwordHash = map["passwordHash"].toString();
    user.signUpTime = map["signUpTime"].toString();
    user.inGameTime = map["inGameTime"].toLongLong();
    QVariantMap inv = map["inventory"].toJsonObject().toVariantMap();
    QMap <QString, int> inventory;
    for (auto i = inv.begin(); i != inv.end(); ++i) {
        inventory[i.key()] = i.value().toInt();
    }
    user.inventory.set() = inventory;
    QVariantMap itemStats = map["itemStats"].toJsonObject().toVariantMap();
    QMap <QString, QMap <QString, int>> itemStatistics;
    for (auto i = itemStats.begin(); i != itemStats.end(); ++i) {
        QVariantMap stat = i.value().toMap();
        QMap <QString, int> statistics;
        for (auto j = stat.begin(); j != stat.end(); ++j) {
            statistics[j.key()] = j.value().toInt();
        }
        itemStatistics[i.key()] = statistics;
    }
    user.inventory.setItemStats() = itemStatistics;
    return QVariant::fromValue(user);
}

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
            statistics["got"] = quantity;
            itemStatistics.insert(name, statistics);
        } else {
            it.value()["got"] += quantity;
        }
    }
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

QString User::getUsername() const {
    return username;
}

QString User::getPasswordHash() const {
    return passwordHash;
}

void User::incClicks() {
    ++clicks;
}

void User::changeCoins(qint64 quantity) {
    if (coins + quantity >= 0) {
        coins += quantity;
    }
}

void User::setPasswordHash(const QString &hashedPassword) {
    passwordHash = hashedPassword;
}

void User::setPrivilegeLevel(int level) {
    privilegeLevel = level;
}

void User::incInGameTime(qint64 time) {
    inGameTime += time;
}

qint64 User::getClicks() const {
    return clicks;
}

qint64 User::getCoins() const {
    return coins;
}

qint64 User::getPrivilegeLevel() const {
    return privilegeLevel;
}

QString User::getInGameTime() const {
    return QDateTime::fromTime_t(inGameTime).toUTC().toString("hh:mm:ss");
}

QVector <QPair<QString, QString>> User::getStatistsics(Game *game) const {
    game->updateTimePlayed();
    QVector <QPair<QString, QString>> result;
    result.push_back({game->str.username, this->getUsername()});
    result.push_back({game->str.coins, QString::number(this->getCoins())});
    result.push_back({game->str.clicksCount, QString::number(this->getClicks())});
    result.push_back({game->str.timePlayed, this->getInGameTime()});
    return result;
}

QVector <QPair<QString, QMap <QString, QString>>> User::getItemStatistsics() const {
    QVector <QPair<QString, QMap <QString, QString>>> result;
    auto item = this->inventory.getItemStats().cbegin();
    while (item != this->inventory.getItemStats().cend()) {
        QMap <QString, QString> options;
        auto option = item.value().cbegin();
        while (option != item.value().cend()) {
            options[option.key()] = QString::number(option.value());
            ++option;
        }
        result.push_back({item.key(), options});
        ++item;
    }
    return result;
}
