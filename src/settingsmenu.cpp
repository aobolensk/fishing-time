#include <QFontDialog>
#include <QMessageBox>
#include "settingsmenu.h"
#include "game.h"

SettingsMenu::SettingsMenu(Game *game, QGridLayout *grid) :
        game(game),
        grid(grid) {
    grid->addWidget(&autoSavePeriodLabel, 0, 0);
    autoSavePeriodLabel.setVisible(false);
    autoSavePeriodLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&autoSavePeriodSelector, 0, 1);
    autoSavePeriodSelector.setCurrentIndex(-1);
    autoSavePeriodSelector.setVisible(false);
    autoSavePeriodSelector.setEnabled(false);

    grid->addWidget(&languageLabel, 1, 0);
    languageLabel.setVisible(false);
    languageLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&languageSelector, 1, 1);
    for (int i = 0; i < game->str.languages.size(); ++i) {
        languageSelector.addItem(game->str.languages[(Language)i].first +
                                 " (" + QString::number(game->str.getReadiness((Language)i)) + "%) ready");
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
    inventoryTypeLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&inventoryTypeSelector, 2, 1);
    inventoryTypeSelector.setCurrentIndex(-1);
    inventoryTypeSelector.setVisible(false);
    inventoryTypeSelector.setEnabled(false);

    grid->addWidget(&fontLabel, 3, 0);
    fontLabel.setVisible(false);
    fontLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&fontSetupButton, 3, 1);
    fontSetupButton.setVisible(false);
    fontSetupButton.setEnabled(false);
    connect(&fontSetupButton, SIGNAL(released()), this, SLOT(fontSetupFunction()));

    grid->addWidget(&eraseAllDataButton, 4, 1);
    eraseAllDataButton.setVisible(false);
    eraseAllDataButton.setEnabled(false);
    connect(&eraseAllDataButton, SIGNAL(released()), this, SLOT(eraseAllDataFunction()));

    grid->addWidget(&backButton, 5, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

bool SettingsMenu::isDisplayed() const {
    return displayed;
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

    fontLabel.setText(game->str.font);
    fontLabel.setVisible(true);

    fontSetupButton.setText(game->str.setup);
    fontSetupButton.setVisible(true);
    fontSetupButton.setEnabled(true);

    eraseAllDataButton.setText(game->str.eraseAllData);
    eraseAllDataButton.setVisible(true);
    eraseAllDataButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

QString SettingsMenu::getSetting(const QString &settingName) {
    if (settingName == "autosave") {
        return QString::number(game->getAutoSavePeriod()) + " minutes";
    } else if (settingName == "language") {
        return game->str.languages[game->activeLanguage].first;
    } else {
        return "";
    }
}

void SettingsMenu::fontSetupFunction() {
    QFont newFont = QFontDialog::getFont(nullptr, game->textFont, nullptr);
    game->setFont(newFont);
    game->console.setFont(newFont);
    game->aboutMenu.setFont(newFont);
}

void SettingsMenu::eraseAllDataFunction() {
    game->gameMenu.logOutFunction();
    QMessageBox::StandardButton eraseResult =
        QMessageBox::question(nullptr, game->str.fishingTime, game->str.eraseAllDataConfirmation,
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
    if (eraseResult == QMessageBox::Yes) {
        if (remove(game->getConfigFileName().toStdString().c_str())) {
            qDebug() << "Error while deleting config file";
        } else {
            qDebug() << "Config file is successfully removed";
        }
    }
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

    fontLabel.setVisible(false);

    fontSetupButton.setVisible(false);
    fontSetupButton.setEnabled(false);

    eraseAllDataButton.setVisible(false);
    eraseAllDataButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

SettingsMenu::~SettingsMenu() {

}
