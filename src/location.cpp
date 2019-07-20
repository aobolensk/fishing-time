#include "location.h"
#include "game.h"

Location::Location(const QString &locName, const QVector <QString> &fishList) :
    name(&locName),
    fish(fishList) {}

QVector <Location> Location::initializeLocations(Game *game) {
    return QVector <Location>({
        Location(game->str.volga, {"fish.carp", "fish.perch", "fish.pike"}),
        Location(game->str.oka, {"fish.bream", "fish.ide", "fish.roach"})
    });
}

const QString &Location::getName() const {
    return *name;
}

const QString &Location::getFish(int index) const {
    return fish[index];
}

int Location::getFishCount() const {
    return fish.size();
}
