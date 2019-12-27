#include "log.h"
#include "game.h"

Log::Log(Game *game) :
        game(game) {}

QString Log::getTimestamp() {
    return "[" + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz") + "]";
}
