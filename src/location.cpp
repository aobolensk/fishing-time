#include "location.h"
#include "mainwindow.h"

Location::Location(MainWindow *w, const QString &locName, const QVector <QString> &fishList) :
    window(w),
    name(locName),
    fish(fishList) {}

QVector <Location> Location::initializeLocations(MainWindow *w) {
    return QVector <Location>({
        Location(w, w->str.volga, {"fish.carp", "fish.perch", "fish.pike"})
    });
}

const QString &Location::getFish(int index) {
    return fish[index];
}
