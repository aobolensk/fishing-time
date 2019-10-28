#include "location.h"
#include "game.h"

Location::Location(
        const QString &locName,             // Location name
        const QVector <QString> &fishList,  // List of fish that can ge caught
        bool hasMarket                      // Is market enabled?
    ) :
    name(&locName),
    fish(fishList),
    hasMarket(hasMarket)
    {}

QVector <Location> Location::initializeLocations(Game *game) {
    return QVector <Location>({
        Location(
            game->str.volga,
            {"fish.carp", "fish.perch", "fish.pike"},
            true
        ),
        Location(
            game->str.oka,
            {"fish.bream", "fish.ide", "fish.roach"},
            true
        )
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

bool Location::getHasMarket() const {
    return hasMarket;
}
