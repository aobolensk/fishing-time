#include <QKeyEvent>
#include "menu.h"
#include "game.h"

Menu::Menu(Game *game, QGridLayout *grid, bool floating) :
    game(game),
    grid(grid),
    floating(floating) {
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
        } else if (key->key() == 72 && (key->modifiers() & Qt::ControlModifier)) { // Ctrl + H
            if (this->displayed) {
                this->hide();
                game->installEventFilter(this);
            } else {
                game->removeEventFilter(this);
                this->display();
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

void Menu::pre_display() {
    if (!this->floating) {
        game->setBackgroundImage(this->backgroundImage);
        if (game->getCurrentMenu() != nullptr) {
            Menu *currentMenu = game->getCurrentMenu();
            game->logger.error("Previous menu (" + QString(typeid(*currentMenu).name()) + ") is not hide!");
        }
        game->setCurrentMenu(this);
        game->logger.debug("Set current menu to " + QString(typeid(*this).name()));
    }
    game->installEventFilter(this);
}

void Menu::pre_hide() {
    if (!this->floating) {
        game->setCurrentMenu(nullptr);
        game->logger.debug("Reset current menu");
    }
    game->removeEventFilter(this);
}

void Menu::backFunction() {

}

Menu::~Menu() {

}
