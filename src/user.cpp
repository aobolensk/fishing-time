#include "user.h"

User::User(const QString &name) :
    username(name) {
    
}

QByteArray User::serialize() {
    QJsonObject jsonObj;
    jsonObj["username"] = username;
    jsonObj["clicks"] = clicks;
    QJsonDocument doc(jsonObj);
    return doc.toJson();
}
