#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_
#include <QLineEdit>
#include <QMap>
#include <QTextEdit>
#include <deque>
#include "log.h"
#include "menu.h"

class Console : public Menu {
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
    public:
        bool needToPush = true;
        void reset();
        void push(const QString &str);
        QString getUpper();
        QString getLower();
    } inputHistory;
private:
    void closeEvent(QCloseEvent *event) override;
protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
private:
    QTextEdit console;
    QLineEdit input;
    TextEditLog log;
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
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_CONSOLE_H_
