#include "log.h"
#include "game.h"

Log::Log(Game *game, QTextEdit *logField) :
    game(game),
    console(logField) {}

void Log::info(const QString &message) {
    console->insertHtml(game->str.logInfo + ' ' + message + "<br>");
}

void Log::warning(const QString &message) {
    console->insertHtml("<font color=\"orange\">" + game->str.logWarning + ' ' + message + "</font><br>");
}

void Log::error(const QString &message) {
    console->insertHtml("<font color=\"red\">" + game->str.logError + ' ' + message + "</font><br>");
}

void Log::write(const QString &message) {
    console->insertHtml(message + ' ');
}

void Log::writeln(const QString &message) {
    console->insertHtml(message + "<br>");
}

void Log::setColor(const QString &color) {
    console->insertHtml(QString("<font color=\"%1\">").arg(color));
}

void Log::resetColor() {
    console->insertHtml("</font>");
}