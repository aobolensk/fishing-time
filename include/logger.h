#ifndef INCLUDE_LOGGER_H_
#define INCLUDE_LOGGER_H_
#include <QTextEdit>
#include <QPushButton>
#include "texteditlog.h"
#include "filelog.h"
#include "config.h"
#include "menu.h"

class Logger : public Menu {
private:
    void closeEvent(QCloseEvent *event) override;
private:
    QTextEdit console;
    QPushButton clearButton,
                jumpToBottomButton;
    TextEditLog log;
    FileLog fileLog;
private slots:
    void clearFunction();
    void jumpToBottomFunction();
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
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
    void setFile(const QString &filePath);
    LoggerLevel getLevel();
};

#endif  // INCLUDE_LOGGER_H_
