#include <QTemporaryFile>
#include <QDataStream>
#include "user.h"

User::User(const QString &name, const QString &password) :
    username(name),
    passwordHash(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5)) {
    
}

template <typename T>
static QString toString(const T &data) {
    QTemporaryFile f;
    f.open();
    QDataStream out(&f);
    out << data;
    f.flush();
    f.close();
    f.open();
    QTextStream in(&f);
    QString result = in.readAll();
    f.close();
    return result;
}

template <typename T>
static void fromString(T &data, const QString &str) {
    QTemporaryFile f;
    f.open();
    QTextStream out(&f);
    out << str;
    f.close();
    f.open();
    QDataStream in(&f);
    in >> data;
    f.close();
}

QJsonObject User::serialize() const {
    QJsonObject jsonObj;
    jsonObj["fishingtime_object"] = "user";
    jsonObj["username"] = username;
    jsonObj["clicks"] = clicks;
    jsonObj["coins"] = coins;
    jsonObj["passwordHash"] = toString(passwordHash);
    jsonObj["inventory"] = toString(inventory.get());
    return jsonObj;
}

QVariant User::deserialize(const QVariantMap &map) {
    User user = User(map["username"].toString());
    user.clicks = map["clicks"].toLongLong();
    user.coins = map["coins"].toLongLong();
    fromString(user.passwordHash, map["passwordHash"].toString());
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

QByteArray User::getPasswordHash() const {
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

qint64 User::getClicks() const {
    return clicks;
}

qint64 User::getCoins() const {
    return coins;
}
