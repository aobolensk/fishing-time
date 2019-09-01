#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_
#include <deque>
#include <functional>
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QMap>
#include "log.h"

class Game;

class Console : public QWidget {
private:
    struct Command {
        std::function <int(QStringList &)> function;
        QString description;
        Command() = default;
        ~Command() = default;
    };
    std::deque <QString> inputHistory;
protected:
    bool eventFilter(QObject *obj, QEvent *event);
private:
    Game *game;
    QGridLayout grid;
    QTextEdit console;
    QLineEdit input;
    Log log;
    QMap <QString, Command> commands;
private:
    void parse(QStringList &args);
    void registerCommands();
private slots:
    void commandParser();
public:
    Console(Game *game = nullptr);
    ~Console() = default;
    void display();
    void hide();
};

#endif  // INCLUDE_CONSOLE_H_
