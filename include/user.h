#ifndef INCLUDE_USER_H_
#define INCLUDE_USER_H_
#include <QJsonObject>
#include <QString>
#include <QVariant>
#include "menu.h"

class User {
private:
    // General information
    QString username;
    QString passwordHash;
    qint64 coins = 0ll;
    qint64 experience = 0ll;
    int privilegeLevel = 0;
    int lastTicketDay = 0;
    // Statistics
    QString signUpTime;
    qint64 clicks = 0ll;
    qint64 inGameTime = 0ll;
public:
    class Inventory {
    public:
    private:
        QMap <QString, int> inventory;
        QMap <QString, QMap <QString, int>> itemStatistics;
    public:
        int getItem(const QString &name);
        void changeItem(const QString &name, int quantity);
        void updateStats(const QString &name, const QString &stat, int quantity);
        const QMap <QString, int> &get() const;
        const QMap <QString, QMap <QString, int>> &getItemStats() const;
        QMap <QString, int> &set();
        QMap <QString, QMap <QString, int>> &setItemStats();
    } inventory;
    // Object creation & deletion
    User(const QString &name = "", const QString &password = "");
    ~User() = default;
    // Serialization
    QJsonObject serialize() const;
    static QVariant deserialize(const QVariantMap &map);
    // Setters
    void incClicks();
    void changeExperience(qint64 quantity);
    void changeCoins(qint64 quantity);
    void setPasswordHash(const QString &hashedPassword);
    void setPrivilegeLevel(int level);
    void incInGameTime(qint64 time);
    void updateLastTicketDay();
    // Getters
    QString getUsername() const;
    QString getPasswordHash() const;
    qint64 getClicks() const;
    qint64 getCoins() const;
    qint64 getExperience() const;
    int getLevel() const;
    qint64 getRemainingForNextLevel() const;
    qint64 getNeededForNextLevel() const;
    qint64 getPrivilegeLevel() const;
    QString getInGameTime() const;
    bool canGetTicket() const;
    // Statistics
    QVector <QPair<QString, QString>> getStatistsics(Game *game) const;
    QVector <QPair<QString, QMap <QString, QString>>> getItemStatistsics() const;
};

Q_DECLARE_METATYPE(User)

#endif  // INCLUDE_USER_H_
