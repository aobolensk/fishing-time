#include "filelog.h"
#include "game.h"

FileLog::FileLog(Game *game, const QString &filePath) :
    Log(game),
    file(QFile(filePath)),
    fs(nullptr) {
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "Failed to open file '" << filePath << "' for logging";
    }
    fs = new QTextStream(&file);
}

void FileLog::debug(const QString &message) {
    if (game->loggerLevel == LoggerLevel::DEBUG) {
        *fs << game->str.logDebug << ' ' << message << '\n';
    }
}

void FileLog::info(const QString &message) {
    *fs << game->str.logInfo << ' ' << message << '\n';
}

void FileLog::warning(const QString &message) {
    *fs << game->str.logWarning << ' ' << message << '\n';
}

void FileLog::error(const QString &message) {
    *fs << game->str.logError << ' ' << message << '\n';
}

void FileLog::debugT(const QString &message) {
    if (game->loggerLevel == LoggerLevel::DEBUG) {
        *fs << getTimestamp() << ' ' << game->str.logDebug << ' ' << message << '\n';
    }
}

void FileLog::infoT(const QString &message) {
    *fs << getTimestamp() << ' ' << game->str.logInfo << ' ' << message << '\n';
}

void FileLog::warningT(const QString &message) {
    *fs << getTimestamp() << ' ' << game->str.logWarning << ' ' << message << '\n';
}

void FileLog::errorT(const QString &message) {
    *fs << getTimestamp() << ' ' << game->str.logError << ' ' << message << '\n';
}

void FileLog::write(const QString &message) {
    *fs << message << ' ';
}

void FileLog::writeln(const QString &message) {
    *fs << message << '\n';
}

void FileLog::setColor(const QString &color) {
    (void)color;
}

void FileLog::resetColor() {

}

FileLog::~FileLog() {
    delete fs;
}
