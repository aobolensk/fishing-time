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
    class Inventory {
    private:
        QMap <QString, int> inventory;
    public:
        int getItem(const QString &name);
        void changeItem(const QString &name, int quantity);
        const QMap <QString, int> &get() const;
        QMap <QString, int> &set();
    } inventory;
    // Object creation & deletion
    User(const QString &name = "");
    ~User() = default;
    // Serialization
    QByteArray serialize() const;
    static QVariant deserialize(const QByteArray &data);
    // Setters
    void incClicks();
    // Getters
    qint64 getClicks();
    QString getUsername() const;
};

Q_DECLARE_METATYPE(User)

#endif  // INCLUDE_USER_H_
