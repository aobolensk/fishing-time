#include "location.h"
#include "game.h"

Location::Location(
        const QString &locId,               // Location id
        const QVector <QString> &fishList,  // List of fish that can ge caught
        bool hasMarket                      // Is market enabled?
    ) :
    id(locId),
    fish(fishList),
    hasMarket(hasMarket)
    {}

QVector <Location> Location::initializeLocations(Game *game) {
    return QVector <Location>({
        Location(
            "location.volga",
            {"fish.carp", "fish.perch", "fish.pike"},
            true
        ),
        Location(
            "location.oka",
            {"fish.bream", "fish.ide", "fish.roach"},
            true
        )
    });
}

const QString &Location::getId() const {
    return id;
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
