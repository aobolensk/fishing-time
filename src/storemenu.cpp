#include "storemenu.h"
#include "mainwindow.h"

StoreMenu::StoreMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        storeTable(window),
        grid(g) {
    grid->addWidget(&storeTable, 1, 0, 1, 3);
    storeTable.setRowCount(0);
    storeTable.setColumnCount(2);
    storeTable.setVisible(false);

    grid->addWidget(&quantityText, 0, 0);
    quantityText.setText("0");
    quantityText.setVisible(false);

    grid->addWidget(&buyButton, 0, 1);
    buyButton.setVisible(false);
    connect(&buyButton, SIGNAL(released()), this, SLOT(buyFunction()));

    grid->addWidget(&backButton, 0, 2);
    backButton.setVisible(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void StoreMenu::display() {
    storeTable.setVisible(true);

    quantityText.setVisible(true);

    buyButton.setText(window->str.buy);
    buyButton.setVisible(true);

    backButton.setText(window->str.back);
    backButton.setVisible(true);
}

void StoreMenu::buyFunction() {

}

void StoreMenu::backFunction() {
    this->hide();
    window->gameMenu.display();
}

void StoreMenu::hide() {
    storeTable.setVisible(false);
    quantityText.setVisible(false);
    buyButton.setVisible(false);
    backButton.setVisible(false);
}

StoreMenu::~StoreMenu() {

}
