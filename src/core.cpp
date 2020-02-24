#include "core.h"

Core::Core() :
        #ifndef __MINGW32__
            randomGenerator(rd()),
        #else
            randomGenerator(static_cast<unsigned>(time(nullptr))),
        #endif  // __MINGW32__
        cfg(),
        str(),
        locations(Location::initializeLocations()) {

}
