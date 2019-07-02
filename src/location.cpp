#include "location.h"

Location::Location(const QString &locName, const QVector <QString> &fishList) :
    name(locName),
    fish(fishList) {}

QVector <Location> Location::initializeLocations() {
    return QVector <Location>({
        Location("location1", {"Carp", "Perch", "Pike"})
    });
}

QString Location::getFishName(int index) {
    return fish[index];
}
