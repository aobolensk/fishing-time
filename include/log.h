#ifndef INCLUDE_LOG_H_
#define INCLUDE_LOG_H_
#include <QTextEdit>

class Game;

class Log {
private:
    Game *game;
    QTextEdit *console;
    QString getTimestamp();
public:
    void debug(const QString &message);
    void info(const QString &message);
    void warning(const QString &message);
    void error(const QString &message);
    void debugT(const QString &message);
    void infoT(const QString &message);
    void warningT(const QString &message);
    void errorT(const QString &message);
    void write(const QString &message);
    void writeln(const QString &message);
    void setColor(const QString &color);
    void resetColor();
    Log(Game *game, QTextEdit *logField);
    ~Log() = default;
};

#endif  // INCLUDE_LOG_H_
