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
public:
    Console(Game *game = nullptr);
    ~Console() = default;
    void display();
    void hide();
};

#endif  // INCLUDE_CONSOLE_H_
