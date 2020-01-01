#include <QApplication>
#include <QCryptographicHash>
#include <QDateTime>
#include "game.h"
#include "user.h"

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
    jsonObj["experience"] = experience;
    jsonObj["privilegeLevel"] = privilegeLevel;
    jsonObj["lastTicketDay"] = lastTicketDay;
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
    user.experience = map["experience"].toLongLong();
    user.privilegeLevel = map["privilegeLevel"].toInt();
    user.lastTicketDay = map["lastTicketDay"].toInt();
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

QString User::getUsername() const {
    return username;
}

QString User::getPasswordHash() const {
    return passwordHash;
}

void User::incClicks() {
    ++clicks;
}

void User::changeExperience(qint64 quantity) {
    experience += quantity;
}

void User::changeCoins(qint64 quantity) {
    if (coins + quantity >= 0) {
        if (quantity >= 0) {
            gotCoins += quantity;
        } else {
            spentCoins -= quantity;
        }
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

void User::updateLastTicketDay() {
    lastTicketDay = QDateTime::currentDateTime().daysTo(QDateTime(QDate(2019, 1, 1), QTime(0, 0)));
}

void User::incEarnedCoins(qint64 coins) {
    earnedCoins += coins;
}

void User::incWonCoins(qint64 coins) {
    wonCoins += coins;
}

qint64 User::getClicks() const {
    return clicks;
}

qint64 User::getCoins() const {
    return coins;
}

qint64 User::getExperience() const {
    return experience;
}

int User::getLevel() const {
    int l = 0, r = 56;
    int level = 0;
    while (l <= r) {
        int c = (l + r) / 2;
        if (100ll * (1ll << c) > experience) {
            r = c - 1;
        } else {
            level = c;
            l = c + 1;
        }
    }
    return level;
}

qint64 User::getRemainingForNextLevel() const {
    int level = getLevel();
    return 100ll * (1ll << (level + 1)) - experience;
}

qint64 User::getNeededForNextLevel() const {
    int level = getLevel();
    return 100ll * (1ll << (level + 1)) - (level > 0 ? 100ll * (1ll << level) : 0);
}

qint64 User::getPrivilegeLevel() const {
    return privilegeLevel;
}

QString User::getInGameTime() const {
    return QDateTime::fromTime_t(inGameTime).toUTC().toString("hh:mm:ss");
}

bool User::canGetTicket() const {
    return QDateTime::currentDateTime().daysTo(QDateTime(QDate(2019, 1, 1), QTime(0, 0))) < lastTicketDay;
}

QVector <QPair<QString, QString>> User::getStatistics(Game *game) const {
    game->updateTimePlayed();
    QVector <QPair<QString, QString>> result;
    result.push_back({game->str.username, this->getUsername()});
    result.push_back({game->str.coins, QString::number(this->getCoins())});
    result.push_back({game->str.totalGotCoins, QString::number(this->gotCoins)});
    result.push_back({game->str.totalEarnedCoins, QString::number(this->earnedCoins)});
    result.push_back({game->str.totalWonCoins, QString::number(this->wonCoins)});
    result.push_back({game->str.totalSpentCoins, QString::number(this->spentCoins)});
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
