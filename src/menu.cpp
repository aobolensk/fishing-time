#include <QDebug>
#include <QKeyEvent>
#include "menu.h"

Menu::Menu(Game *game, QGridLayout *grid) :
    game(game),
    grid(grid) {
    if (!this->grid) {
        this->grid = new QGridLayout(this);
    }
}

bool Menu::isDisplayed() const {
    return displayed;
}

bool Menu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        qDebug() << typeid(*this).name() << "->" << key->key();
        if (key->key() == 16777216) { // escape
            this->backFunction();
        }
    }
    return QObject::eventFilter(obj, event);
}

void Menu::pre_display() {

}

void Menu::pre_hide() {

}

void Menu::backFunction() {

}

Menu::~Menu() {

}
