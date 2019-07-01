#include "gamemenu.h"
#include "mainwindow.h"

GameMenu::GameMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        clickButton(QPushButton(window)),
        backButton(QPushButton(window)),
        inventoryButton(QPushButton(window)),
        infoLabel(QLabel(window)),
        table(QTableWidget(nullptr)),
        nameWidget(QTableWidgetItem("Name")),
        quantityWidget(QTableWidgetItem("Quantity")),
        grid(g) {
    table.setRowCount(0);
    table.setColumnCount(2);
    table.setHorizontalHeaderItem(0, &nameWidget);
    table.setHorizontalHeaderItem(1, &quantityWidget);
    table.setVisible(false);
    grid->addWidget(&infoLabel, 0, 0);
    infoLabel.setVisible(false);
    grid->addWidget(&clickButton, 1, 1);
    clickButton.setVisible(false);
    grid->addWidget(&backButton, 1, 2);
    backButton.setVisible(false);
    grid->addWidget(&inventoryButton, 2, 2);
    inventoryButton.setVisible(false);
}

void GameMenu::display() {
    updateInfo();
    infoLabel.setVisible(true);
    clickButton.setText("Click");
    clickButton.setVisible(true);
    connect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));
    backButton.setText("Back");
    backButton.setVisible(true);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
    inventoryButton.setText("Inventory");
    inventoryButton.setVisible(true);
    connect(&inventoryButton, SIGNAL(released()), this, SLOT(inventoryFunction()));
}

void GameMenu::clickFunction() {
    window->users[window->activeUser].incClicks();
    updateInfo();
}

void GameMenu::backFunction() {
    window->activeUser = -1;
    this->hide();
    window->mainMenu.display();
}

void GameMenu::inventoryFunction() {
    window->users[window->activeUser].inventory.changeItem("zulul", 10);
    window->users[window->activeUser].inventory.changeItem("abacaba", 5);
    auto inv = window->users[window->activeUser].inventory.get();
    table.setRowCount(inv.size());
    QMap<QString, int>::const_iterator it = inv.constBegin();
    int i = 0;
    while (it != inv.constEnd()) {
        QTableWidgetItem *cell = table.item(i, 0);
        if (!cell) {
            cell = new QTableWidgetItem;
            table.setItem(i, 0, cell);
        }
        cell->setText(it.key());
        cell = table.item(i, 1);
        if (!cell) {
            cell = new QTableWidgetItem;
            table.setItem(i, 1, cell);
        }
        cell->setText(QString::number(it.value()));
        ++it;
        ++i;
    }
    table.setVisible(true);
}

void GameMenu::updateInfo() {
    QString s;
    s += "Welcome, " + window->users[window->activeUser].getUsername() + '\n';
    s += "Clicks: " + QString::number(window->users[window->activeUser].getClicks()) + '\n';
    infoLabel.setText(s);
}

void GameMenu::hide() {
    infoLabel.setVisible(false);
    clickButton.setVisible(false);
    disconnect(&clickButton, SIGNAL(released()), this, SLOT(clickFunction()));
    backButton.setVisible(false);
    disconnect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
    inventoryButton.setVisible(false);
    disconnect(&inventoryButton, SIGNAL(released()), this, SLOT(inventoryFunction()));
}

GameMenu::~GameMenu() {

}
