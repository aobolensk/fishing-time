#include "location.h"
#include "mainwindow.h"

Location::Location(const QString &locName, const QVector <QString> &fishList) :
    name(locName),
    fish(fishList) {}

QVector <Location> Location::initializeLocations(MainWindow *w) {
    return QVector <Location>({
        Location(w->str.volga, {"fish.carp", "fish.perch", "fish.pike"}),
        Location(w->str.oka, {"fish.bream", "fish.ide", "fish.roach"})
    });
}

const QString &Location::getFish(int index) {
    return fish[index];
}

int Location::getFishCount() const {
    return fish.size();
}
