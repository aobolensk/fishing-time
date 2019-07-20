#include "settingsmenu.h"
#include "game.h"

SettingsMenu::SettingsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&autoSavePeriodLabel, 0, 0);
    autoSavePeriodLabel.setVisible(false);

    grid->addWidget(&autoSaveSelector, 0, 1);
    autoSaveSelector.setCurrentIndex(-1);
    autoSaveSelector.setVisible(false);
    autoSaveSelector.setEnabled(false);

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

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void SettingsMenu::display() {
    autoSavePeriodLabel.setText(game->str.autoSavePeriod);
    autoSavePeriodLabel.setVisible(true);

    for (int i = 0; i < 6; ++i) {
        autoSaveSelector.addItem(QString::number(autoSaveOptions[i]) + ' ' + game->str.min);
    }
    autoSaveSelector.setVisible(true);
    autoSaveSelector.setEnabled(true);
    autoSaveSelector.setCurrentIndex(-1);
    int currentPeriod = game->autoSaveTimer.interval() / (60 * 1000);
    for (int i = 0; i < 6; ++i) {
        if (currentPeriod == autoSaveOptions[i]) {
            autoSaveSelector.setCurrentIndex(i);
            break;
        }
    }
    autoSaveUpdater = connect(&autoSaveSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
       [this](int index){ game->setAutoSavePeriod(autoSaveOptions[index]); });

    languageLabel.setText(game->str.language);
    languageLabel.setVisible(true);

    languageSelector.setCurrentIndex((int)game->activeLanguage);
    languageSelector.setVisible(true);
    languageSelector.setEnabled(true);

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

    autoSaveSelector.setVisible(false);
    autoSaveSelector.setEnabled(false);
    disconnect(autoSaveUpdater);
    autoSaveSelector.setCurrentIndex(-1);
    autoSaveSelector.clear();

    languageLabel.setVisible(false);

    languageSelector.setVisible(false);
    languageSelector.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

SettingsMenu::~SettingsMenu() {

}
