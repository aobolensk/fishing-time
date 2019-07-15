#include "settingsmenu.h"
#include "mainwindow.h"

SettingsMenu::SettingsMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    grid->addWidget(&autoSavePeriodText, 0, 0);
    autoSavePeriodText.setVisible(false);

    grid->addWidget(&autoSaveSelector, 0, 1);
    autoSaveSelector.setVisible(false);
    autoSaveSelector.setEnabled(false);
    for (int i = 0; i < 6; ++i) {
        autoSaveSelector.addItem(QString::number(autoSaveOptions[i]) + ' ' + window->str.min);
    }
    connect(&autoSaveSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
       [this](int index){ window->setAutoSavePeriod(autoSaveOptions[index]); });

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void SettingsMenu::display() {
    autoSavePeriodText.setText(window->str.autoSavePeriod);
    autoSavePeriodText.setVisible(true);

    autoSaveSelector.setVisible(true);
    autoSaveSelector.setEnabled(true);

    backButton.setText(window->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void SettingsMenu::backFunction() {
    this->hide();
    window->mainMenu.display();
}

void SettingsMenu::hide() {
    autoSavePeriodText.setVisible(false);

    autoSaveSelector.setVisible(false);
    autoSaveSelector.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

SettingsMenu::~SettingsMenu() {

}
