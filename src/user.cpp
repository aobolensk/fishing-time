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
    jsonObj["inventory"] = toString(inventory.get());
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
    fromString(user.inventory.set(), map["inventory"].toString());
    return QVariant::fromValue(user);
}

void User::Inventory::changeItem(const QString &name, int quantity) {
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

int User::Inventory::getItem(const QString &name) {
    QMap <QString, int>::iterator it = inventory.find(name);
    if (it != inventory.end())
        return it.value();
    return 0;
}

const QMap <QString, int> &User::Inventory::get() const {
    return inventory;
}

QMap <QString, int> &User::Inventory::set() {
    return inventory;
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
    QVector <QPair<QString, QString>> result;
    result.push_back({game->str.username, this->getUsername()});
    result.push_back({game->str.coins, QString::number(this->getCoins())});
    result.push_back({game->str.clicksCount, QString::number(this->getClicks())});
    result.push_back({game->str.timePlayed, this->getInGameTime()});
    return result;
}
