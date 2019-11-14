#include "log.h"
#include "game.h"

Log::Log(Game *game, QTextEdit *logField) :
    game(game),
    console(logField) {}

void Log::info(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        game->str.logInfo + ' ' + message +
        "<br>"
    );
}

QString Log::getTimestamp() {
    return "[" + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss.zzz") + "]";
}

void Log::warning(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        "<font color=\"orange\">" +
        game->str.logWarning + ' ' + message +
        "</font><br>"
    );
}

void Log::error(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        "<font color=\"red\">" +
        game->str.logError + ' ' + message +
        "</font><br>"
    );
}

void Log::infoT(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        getTimestamp() + ' ' +
        game->str.logInfo + ' ' + message +
        "<br>"
    );
}

void Log::warningT(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        "<font color=\"orange\">" +
        getTimestamp() + ' ' +
        game->str.logWarning + ' ' + message +
        "</font><br>"
    );
}

void Log::errorT(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        "<font color=\"red\">" +
        getTimestamp() + ' ' +
        game->str.logError + ' ' + message +
        "</font><br>"
    );
}


void Log::write(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(message + ' ');
}

void Log::writeln(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(message + "<br>");
}

void Log::setColor(const QString &color) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(QString("<font color=\"%1\">").arg(color));
}

void Log::resetColor() {
    console->moveCursor(QTextCursor::End);
    console->insertHtml("</font>");
}
