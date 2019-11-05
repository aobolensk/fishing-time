#ifndef INCLUDE_LOCATION_H_
#define INCLUDE_LOCATION_H_
#include <QVector>

class Game;

class Location {
private:
    const QString id;
    QVector <QString> fish;
    bool hasMarket;
    Location(
        const QString &locId,
        const QVector <QString> &fishList,
        bool hasMarket
    );
public:
    Location() = default;
    ~Location() = default;
    const QString &getId() const;
    const QString &getFish(int index) const;
    bool getHasMarket() const;
    int getFishCount() const;
    static QVector <Location> initializeLocations();
};

#endif  // INCLUDE_LOCATION_H_
