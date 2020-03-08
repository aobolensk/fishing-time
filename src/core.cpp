#include "core.h"

Core::Core() :
        #ifndef __MINGW32__
            randomGenerator(rd()),
        #else
            randomGenerator(static_cast<unsigned>(time(nullptr))),
        #endif  // __MINGW32__
        cfg(this),
        str(),
        locations(Location::initializeLocations()) {

}

void Core::updateTimePlayed() {
    if (activeUser != -1 && userTimestamp.isValid()) {
        users[activeUser].incInGameTime(
            QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000 -
            userTimestamp.toMSecsSinceEpoch() / 1000
        );
        userTimestamp = QDateTime::currentDateTime();
    }
}
