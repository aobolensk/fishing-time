#include <QApplication>
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
        QKeySequence seq = game->controlsMenu.getKeySequence(key);
        qDebug() << typeid(*this).name() << "->" << key->key();
        auto menuCheck = [&]() {
            return this != &game->controlsMenu || !game->controlsMenu.isInEditingMode();
        };
        if (seq == game->cfg.getKey(Controls::GO_TO_PREVIOUS_MENU)) {
            // Go to previous menu
            if (menuCheck()) {
                this->backFunction();
            }
        } else if (seq == game->cfg.getKey(Controls::TOGGLE_FULLSCREEN_MODE)) {
            // Toggle fullscreen mode
            if (menuCheck()) {
                game->window()->setWindowState(
                    game->window()->windowState() ^ Qt::WindowFullScreen
                );
            }
        } else if (seq == game->cfg.getKey(Controls::HIDE_UI_ELEMENTS)) {
            // Hide UI elements
            if (menuCheck()) {
                if (this->displayed) {
                    this->hide();
                    game->installEventFilter(this);
                } else {
                    game->removeEventFilter(this);
                    this->display();
                }
            }
        } else if (seq == game->cfg.getKey(Controls::EXIT_FROM_THE_GAME)) {
            // Exit from the game
            if (menuCheck()) {
                game->hideAll();
                QApplication::quit();
            }
        }
    } else if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *key = static_cast<QMouseEvent *>(event);
        if (key->buttons() & Qt::BackButton) {
            // Go to previous menu
            this->backFunction();
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
