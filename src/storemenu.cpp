#include "storemenu.h"
#include "mainwindow.h"

StoreMenu::StoreMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    grid->addWidget(&backButton, 3, 2);
    backButton.setVisible(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void StoreMenu::display() {
    backButton.setText(window->str.back);
    backButton.setVisible(true);
}

void StoreMenu::backFunction() {
    this->hide();
    window->gameMenu.display();
}

void StoreMenu::hide() {
    backButton.setVisible(false);
}

StoreMenu::~StoreMenu() {

}
