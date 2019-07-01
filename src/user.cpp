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

QString User::getUsername() const {
    return username;
}
