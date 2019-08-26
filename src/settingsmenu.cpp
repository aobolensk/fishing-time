#include "settingsmenu.h"
#include "game.h"

SettingsMenu::SettingsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&autoSavePeriodLabel, 0, 0);
    autoSavePeriodLabel.setVisible(false);

    grid->addWidget(&autoSavePeriodSelector, 0, 1);
    autoSavePeriodSelector.setCurrentIndex(-1);
    autoSavePeriodSelector.setVisible(false);
    autoSavePeriodSelector.setEnabled(false);

    grid->addWidget(&languageLabel, 1, 0);
    languageLabel.setVisible(false);

    grid->addWidget(&languageSelector, 1, 1);
    for (int i = 0; i < game->str.languages.size(); ++i) {
        languageSelector.addItem(game->str.languages[i]);
    }
    qDebug() << (int)game->activeLanguage;
    connect(&languageSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this](int index) {
            this->hide();
            this->game->str.setLanguage(this->game->activeLanguage = (Language)index);
            this->display();
        });
    languageSelector.setVisible(false);
    languageSelector.setEnabled(false);

    grid->addWidget(&inventoryTypeLabel, 2, 0);
    inventoryTypeLabel.setVisible(false);

    grid->addWidget(&inventoryTypeSelector, 2, 1);
    inventoryTypeSelector.setCurrentIndex(-1);
    inventoryTypeSelector.setVisible(false);
    inventoryTypeSelector.setEnabled(false);

    grid->addWidget(&backButton, 3, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void SettingsMenu::display() {
    autoSavePeriodLabel.setText(game->str.autoSavePeriod);
    autoSavePeriodLabel.setVisible(true);

    for (int i = 0; i < 6; ++i) {
        autoSavePeriodSelector.addItem(QString::number(autoSaveOptions[i]) + ' ' + game->str.min);
    }
    autoSavePeriodSelector.setVisible(true);
    autoSavePeriodSelector.setEnabled(true);
    autoSavePeriodSelector.setCurrentIndex(-1);
    int currentPeriod = game->autoSaveTimer.interval() / (60 * 1000);
    for (int i = 0; i < 6; ++i) {
        if (currentPeriod == autoSaveOptions[i]) {
            autoSavePeriodSelector.setCurrentIndex(i);
            break;
        }
    }
    autoSaveUpdater = connect(&autoSavePeriodSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
       [this](int index){ game->setAutoSavePeriod(autoSaveOptions[index]); });

    languageLabel.setText(game->str.language);
    languageLabel.setVisible(true);

    languageSelector.setCurrentIndex((int)game->activeLanguage);
    languageSelector.setVisible(true);
    languageSelector.setEnabled(true);


    inventoryTypeLabel.setText(game->str.inventoryType);
    inventoryTypeLabel.setVisible(true);

    inventoryTypeSelector.addItem(game->str.popUp);
    inventoryTypeSelector.addItem(game->str.builtIn);
    inventoryTypeSelector.setCurrentIndex((int)game->inventoryType);
    inventoryTypeSelector.setVisible(true);
    inventoryTypeSelector.setEnabled(true);
    inventoryTypeUpdater = connect(&inventoryTypeSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
       [this](int index){ this->game->inventoryType = (InventoryType)index; });

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void SettingsMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void SettingsMenu::hide() {
    autoSavePeriodLabel.setVisible(false);

    autoSavePeriodSelector.setVisible(false);
    autoSavePeriodSelector.setEnabled(false);
    disconnect(autoSaveUpdater);
    autoSavePeriodSelector.clear();

    languageLabel.setVisible(false);

    languageSelector.setVisible(false);
    languageSelector.setEnabled(false);

    inventoryTypeLabel.setVisible(false);

    inventoryTypeSelector.setVisible(false);
    inventoryTypeSelector.setEnabled(false);
    disconnect(inventoryTypeUpdater);
    inventoryTypeSelector.clear();

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

SettingsMenu::~SettingsMenu() {

}
