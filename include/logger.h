#ifndef INCLUDE_LOGGER_H_
#define INCLUDE_LOGGER_H_
#include <QTextEdit>
#include "texteditlog.h"
#include "filelog.h"
#include "config.h"
#include "menu.h"

class Logger : public Menu {
private:
    void closeEvent(QCloseEvent *event) override;
private:
    QTextEdit console;
    TextEditLog log;
    FileLog fileLog;
public:
    void debug(const QString &message);
    void info(const QString &message);
    void warning(const QString &message);
    void error(const QString &message);
public:
    Logger(Game *game = nullptr);
    ~Logger() = default;
    void display() override;
    void hide() override;
    void setLevel(LoggerLevel level);
    LoggerLevel getLevel();
};

#endif  // INCLUDE_LOGGER_H_
