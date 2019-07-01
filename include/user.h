#ifndef INCLUDE_USER_H_
#define INCLUDE_USER_H_
#include <QString>
#include <QByteArray>
#include <QVariant>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QCoreApplication>

class User {
private:
    // General information
    QString username;
    // Statistics
    qint64 clicks = 0ll;
public:
    User(const QString &name = "");
    ~User() = default;
    QByteArray serialize() const;
    static QVariant deserialize(const QByteArray &data) {
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
    QString getUsername() const;
    void incClicks();
    qint64 getClicks();
};

Q_DECLARE_METATYPE(User);

#endif  // INCLUDE_USER_H_
