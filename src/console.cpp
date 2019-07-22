#include "console.h"
#include "game.h"

Console::Console(Game *game) :
    QWidget(),
    game(game),
    grid(QGridLayout(this)) {
    this->setGeometry(QRect(QPoint(740, 100), QSize(360, 480)));
    this->setLayout(&grid);

    grid.addWidget(&console, 0, 0);
    console.setReadOnly(true);
    grid.addWidget(&input, 1, 0);

    this->display();
}

void Console::display() {
    this->show();
}

void Console::hide() {
    this->QWidget::hide();
}
