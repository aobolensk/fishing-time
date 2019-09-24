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
    enum class PrivilegeLevel {
        Common = 0,
        Super
    };
    struct Command {
        std::function <int(QStringList &)> function;
        PrivilegeLevel privilege;
        const QString *description;
        Command() = default;
        ~Command() = default;
    };
    class InputHistory {
    private:
        std::deque <QString> buffer = {""};
        size_t index = 0;
        bool afterPush = false;
    public:
        void push(const QString &str);
        QString getUpper();
        QString getLower();
    } inputHistory;
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
    int parseCommand(QStringList &args);
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
