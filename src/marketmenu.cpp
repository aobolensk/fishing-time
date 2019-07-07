#include <random>
#include "gamemenu.h"
#include "mainwindow.h"

MarketMenu::MarketMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        backButton(QPushButton(window)),
        dialog1Button(QPushButton(window)),
        dialog2Button(QPushButton(window)),
        dialog3Button(QPushButton(window)),
        grid(g) {
    grid->addWidget(&dialog1Button, 2, 0);
    dialog1Button.setVisible(false);

    grid->addWidget(&dialog2Button, 2, 1);
    dialog2Button.setVisible(false);

    grid->addWidget(&dialog3Button, 2, 2);
    dialog3Button.setVisible(false);

    grid->addWidget(&backButton, 3, 2);
    backButton.setVisible(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void MarketMenu::display() {
    dialog1Button.setText(window->str.dialog);
    dialog1Button.setVisible(true);

    dialog2Button.setText(window->str.dialog);
    dialog2Button.setVisible(true);

    dialog3Button.setText(window->str.dialog);
    dialog3Button.setVisible(true);

    backButton.setText(window->str.back);
    backButton.setVisible(true);
}

void MarketMenu::backFunction() {
    this->hide();
    window->gameMenu.display();
}

void MarketMenu::hide() {
    dialog1Button.setVisible(false);
    dialog2Button.setVisible(false);
    dialog3Button.setVisible(false);
    backButton.setVisible(false);
}

MarketMenu::~MarketMenu() {

}
