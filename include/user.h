#ifndef INCLUDE_USER_H_
#define INCLUDE_USER_H_
#include <QString>
#include <QByteArray>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>

class User {
private:
    // General information
    QString username;
    // Statistics
    qint64 clicks;
public:
    User() = delete;
    User(const QString &name);
    ~User() = default;
    QByteArray serialize();
    User deserialize(const QByteArray &data) {
        QVariantMap map = QJsonDocument::fromJson(data).object().toVariantMap();
        User user = User(map["username"].toString());
        user.clicks = map["clicks"].toLongLong();
        return user;
    }
};

#endif  // INCLUDE_USER_H_
