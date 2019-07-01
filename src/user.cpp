#include "user.h"

User::User(const QString &name) :
    username(name) {
    
}

QByteArray User::serialize() const {
    QJsonObject jsonObj;
    jsonObj["ftobj_type"] = "user";
    jsonObj["username"] = username;
    jsonObj["clicks"] = clicks;
    QJsonDocument doc(jsonObj);
    return doc.toJson();
}

QVariant User::deserialize(const QByteArray &data) {
    QJsonParseError jsonParseError;
    QVariantMap map = QJsonDocument::fromJson(data, &jsonParseError)
            .object().toVariantMap();
    if (map["ftobj_type"] != QString("user")) {
        qDebug() << map["ftobj_type"];
        return QVariant();
    }
    if (jsonParseError.error != QJsonParseError::NoError) {
        qDebug() << jsonParseError.errorString();
        return QVariant();
    }
    User user = User(map["username"].toString());
    user.clicks = map["clicks"].toLongLong();
    return QVariant::fromValue(user);
}

void User::Inventory::changeItem(const QString &name, int quantity) {
    QMap <QString, int>::iterator it = inventory.find(name);
    if (it != inventory.end()) {
        if (quantity <= 0)
            return;
        inventory.insert(name, quantity);
    } else {
        it.value() -= quantity;
        if (it.value() <= 0)
            inventory.erase(it);
    }
}

QString User::getUsername() const {
    return username;
}

void User::incClicks() {
    ++clicks;
}

qint64 User::getClicks() {
    return clicks;
}

int User::Inventory::getItem(const QString &name) {
    QMap <QString, int>::iterator it = inventory.find(name);
    if (it != inventory.end())
        return it.value();
    return 0;
}
