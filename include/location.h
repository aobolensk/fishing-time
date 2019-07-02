#ifndef INCLUDE_LOCATION_H_
#define INCLUDE_LOCATION_H_
#include <QVector>

class Location {
private:
    QString name;
    QVector <QString> fish;
public:
    Location(const QString &locName = "", const QVector <QString> &fishList = {});
    ~Location() = default;
    QString getFishName(int index);
    static QVector <Location> initializeLocations();
};

#endif  // INCLUDE_LOCATION_H_
