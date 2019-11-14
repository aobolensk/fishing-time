#ifndef INCLUDE_LOGGER_H_
#define INCLUDE_LOGGER_H_
#include <QTextEdit>
#include "log.h"
#include "menu.h"

class Logger : public Menu {
private:
    void closeEvent(QCloseEvent *event) override;
private:
    QTextEdit console;
    Log log;
public:
    Logger(Game *game = nullptr);
    ~Logger() = default;
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_LOGGER_H_
