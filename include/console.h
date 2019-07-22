#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>

class Game;

class Console : public QWidget {
private:
    Game *game;
    QGridLayout grid;
    QTextEdit console;
    QLineEdit input;
private:
    struct Log {
        QTextEdit *console;
        Log(QTextEdit *field);
        void info(const QString &message, bool newLine = true);
        void warning(const QString &message, bool newLine = true);
        void error(const QString &message, bool newLine = true);
    } log;
private slots:
    void commandParser();
public:
    Console(Game *game = nullptr);
    ~Console() = default;
    void display();
    void hide();
};

#endif  // INCLUDE_CONSOLE_H_
