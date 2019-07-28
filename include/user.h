#ifndef INCLUDE_USER_H_
#define INCLUDE_USER_H_
#include <QString>
#include <QByteArray>
#include <QVariant>
#include <QJsonObject>
#include <QDebug>
#include <QCoreApplication>
#include <QCryptographicHash>

class User {
private:
    // General information
    QString username;
    QByteArray passwordHash;
    qint64 coins = 0ll;
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
    User(const QString &name = "", const QString &password = "");
    ~User() = default;
    // Serialization
    QJsonObject serialize() const;
    static QVariant deserialize(const QVariantMap &map);
    // Setters
    void incClicks();
    void changeCoins(qint64 quantity);
    void setPasswordHash(const QByteArray &hashedPassword);
    // Getters
    QString getUsername() const;
    QByteArray getPasswordHash() const;
    qint64 getClicks() const;
    qint64 getCoins() const;
};

Q_DECLARE_METATYPE(User)

#endif  // INCLUDE_USER_H_
