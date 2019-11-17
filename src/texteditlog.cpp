#include "texteditlog.h"
#include "game.h"

TextEditLog::TextEditLog(Game *game, QTextEdit *logField) :
    Log(game),
    console(logField) {}

void TextEditLog::debug(const QString &message) {
    if (game->loggerLevel == LoggerLevel::DEBUG) {
        console->moveCursor(QTextCursor::End);
        console->insertHtml(
            game->str.logDebug + ' ' + message +
            "<br>"
        );
    }
}

void TextEditLog::info(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        game->str.logInfo + ' ' + message +
        "<br>"
    );
}

void TextEditLog::warning(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        "<font color=\"orange\">" +
        game->str.logWarning + ' ' + message +
        "</font><br>"
    );
}

void TextEditLog::error(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        "<font color=\"red\">" +
        game->str.logError + ' ' + message +
        "</font><br>"
    );
}

void TextEditLog::debugT(const QString &message) {
    if (game->loggerLevel == LoggerLevel::DEBUG) {
        console->moveCursor(QTextCursor::End);
        console->insertHtml(
            getTimestamp() + ' ' +
            game->str.logDebug + ' ' + message +
            "<br>"
        );
    }
}

void TextEditLog::infoT(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        getTimestamp() + ' ' +
        game->str.logInfo + ' ' + message +
        "<br>"
    );
}

void TextEditLog::warningT(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        "<font color=\"orange\">" +
        getTimestamp() + ' ' +
        game->str.logWarning + ' ' + message +
        "</font><br>"
    );
}

void TextEditLog::errorT(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(
        "<font color=\"red\">" +
        getTimestamp() + ' ' +
        game->str.logError + ' ' + message +
        "</font><br>"
    );
}

void TextEditLog::write(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(message + ' ');
}

void TextEditLog::writeln(const QString &message) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(message + "<br>");
}

void TextEditLog::setColor(const QString &color) {
    console->moveCursor(QTextCursor::End);
    console->insertHtml(QString("<font color=\"%1\">").arg(color));
}

void TextEditLog::resetColor() {
    console->moveCursor(QTextCursor::End);
    console->insertHtml("</font>");
}
