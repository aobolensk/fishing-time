#include <QTemporaryFile>
#include <QDataStream>
#include "user.h"

User::User(const QString &name) :
    username(name) {
    
}

QByteArray User::serialize() const {
    QJsonObject jsonObj;
    jsonObj["ftobj_type"] = "user";
    jsonObj["username"] = username;
    jsonObj["clicks"] = clicks;
    jsonObj["coins"] = coins;
    QMap<QString, int>::const_iterator it = inventory.get().constBegin();
    while (it != inventory.get().constEnd()) {
        qDebug() << it.key() << it.value();
        ++it;
    }
    QTemporaryFile f;
    f.open();
    QDataStream out(&f);
    out << inventory.get();
    f.flush();
    f.close();
    f.open();
    QTextStream in(&f);
    QString buf = in.readAll();
    f.close();
    qDebug() << "Inventory:" << buf;
    jsonObj["inventory"] = buf;
    QJsonDocument doc(jsonObj);
    return doc.toJson();
}

QVariant User::deserialize(const QVariantMap &map) {
    User user = User(map["username"].toString());
    user.clicks = map["clicks"].toLongLong();
    user.coins = map["coins"].toLongLong();
    QString buf = map["inventory"].toString();
    qDebug() << "Inventory:" << buf;
    QTemporaryFile f;
    f.open();
    QTextStream out(&f);
    out << buf;
    f.close();
    f.open();
    QDataStream in(&f);
    in >> user.inventory.set();
    f.close();
    QMap<QString, int>::const_iterator it = user.inventory.get().constBegin();
    while (it != user.inventory.get().constEnd()) {
        qDebug() << it.key() << it.value();
        ++it;
    }
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
