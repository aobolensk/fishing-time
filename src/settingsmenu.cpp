#include <QFileDialog>
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

    grid->addWidget(&autoSavePeriodSlider, 0, 1);
    autoSavePeriodSlider.setOrientation(Qt::Horizontal);
    autoSavePeriodSlider.setRange(Config::MIN_AUTO_SAVE_PERIOD, Config::MAX_AUTO_SAVE_PERIOD);
    autoSavePeriodSlider.setVisible(false);
    autoSavePeriodSlider.setEnabled(false);

    grid->addWidget(&autoSavePeriodValueLabel, 0, 2);
    autoSavePeriodValueLabel.setVisible(false);

    grid->addWidget(&languageLabel, 1, 0);
    languageLabel.setVisible(false);
    languageLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&languageSelector, 1, 1);
    for (int i = 0; i < game->str.languages.size(); ++i) {
        languageSelector.addItem(game->str.languages[(Language)i].first + " (" +
            QString::number(game->str.getNumberOfEntries((Language)i)) + "/" +
            QString::number(game->str.getTotalNumberOfEntries()) + " -> " +
            QString::number(game->str.getReadiness((Language)i)) + "%) ready");
    }
    qDebug() << (int)game->activeLanguage;

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

    grid->addWidget(&colorThemeLabel, 4, 0);
    colorThemeLabel.setVisible(false);
    colorThemeLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&colorThemeSelector, 4, 1);
    colorThemeSelector.setCurrentIndex(-1);
    colorThemeSelector.setVisible(false);
    colorThemeSelector.setEnabled(false);

    grid->addWidget(&eraseAllDataButton, 5, 1);
    eraseAllDataButton.setVisible(false);
    eraseAllDataButton.setEnabled(false);
    connect(&eraseAllDataButton, SIGNAL(released()), this, SLOT(eraseAllDataFunction()));

    grid->addWidget(&configFileLabel, 6, 0);
    configFileLabel.setVisible(false);
    configFileLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&configFileSetupButton, 6, 1);
    configFileSetupButton.setVisible(false);
    configFileSetupButton.setEnabled(false);
    connect(&configFileSetupButton, SIGNAL(released()), this, SLOT(configFileSetupFunction()));

    grid->addWidget(&backButton, 7, 1);
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

    autoSavePeriodSlider.setValue(game->getAutoSavePeriod());
    autoSavePeriodSlider.setVisible(true);
    autoSavePeriodSlider.setEnabled(true);
    autoSaveUpdater = connect(&autoSavePeriodSlider, SIGNAL(valueChanged(int)), this, SLOT(autoSavePeriodSliderFunction(int)));

    autoSavePeriodValueLabel.setText(QString::number(game->getAutoSavePeriod()));
    autoSavePeriodValueLabel.setVisible(true);

    languageLabel.setText(game->str.language);
    languageLabel.setVisible(true);

    languageSelector.setCurrentIndex((int)game->activeLanguage);
    languageSelector.setVisible(true);
    languageSelector.setEnabled(true);
    languageUpdater = connect(&languageSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this](int index) {
            this->hide();
            this->game->str.setLanguage(this->game->activeLanguage = (Language)index);
            this->display();
        });

    inventoryTypeLabel.setText(game->str.inventoryType);
    inventoryTypeLabel.setVisible(true);

    inventoryTypeSelector.addItem(game->str.popUp);
    inventoryTypeSelector.addItem(game->str.builtIn);
    inventoryTypeSelector.setCurrentIndex((int)game->inventoryType);
    inventoryTypeSelector.setVisible(true);
    inventoryTypeSelector.setEnabled(true);
    inventoryTypeUpdater = connect(&inventoryTypeSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
    [this](int index) {
        if (index != -1) {
            this->game->inventoryType = (InventoryType)index;
        }
    });

    fontLabel.setText(game->str.font);
    fontLabel.setVisible(true);

    fontSetupButton.setText(game->str.setup);
    fontSetupButton.setVisible(true);
    fontSetupButton.setEnabled(true);

    colorThemeLabel.setText(game->str.colorTheme);
    colorThemeLabel.setVisible(true);

    colorThemeSelector.addItem(game->str.lightTheme);
    colorThemeSelector.addItem(game->str.darkTheme);
    colorThemeSelector.setCurrentIndex((int)game->colorTheme);
    colorThemeSelector.setVisible(true);
    colorThemeSelector.setEnabled(true);
    colorThemeUpdater = connect(&colorThemeSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
    [this](int index) {
        if (index != -1) {
            this->game->colorTheme = (ColorTheme)index;
            this->game->cfg.applyColorTheme(this->game->colorTheme);
        }
    });

    eraseAllDataButton.setText(game->str.eraseAllData);
    eraseAllDataButton.setVisible(true);
    eraseAllDataButton.setEnabled(true);

    configFileLabel.setText(game->str.configFile);
    configFileLabel.setVisible(true);

    configFileSetupButton.setText(game->str.open);
    configFileSetupButton.setVisible(true);
    configFileSetupButton.setEnabled(true);

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
    game->gameMenu.getPopUpInventoryTable().setFont(newFont);
}

void SettingsMenu::configFileSetupFunction() {
    QString config_file = QFileDialog::getOpenFileName();
    qDebug() << "New config file:" << config_file;
    if (config_file.size() > 0) {
        game->setConfigFile(config_file);
    }
}

void SettingsMenu::eraseAllDataFunction() {
    QMessageBox::StandardButton eraseResult =
        QMessageBox::question(nullptr, game->str.fishingTime, game->str.eraseAllDataConfirmation,
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
    if (eraseResult == QMessageBox::Yes) {
        game->gameMenu.logOutFunction();
        if (remove(game->getConfigFileName().toStdString().c_str())) {
            qDebug() << "Error while deleting config file";
        } else {
            qDebug() << "Config file is successfully removed";
        }
    }
}

void SettingsMenu::autoSavePeriodSliderFunction(int value) {
    game->setAutoSavePeriod(value);
    autoSavePeriodValueLabel.setText(QString::number(value));
}

void SettingsMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void SettingsMenu::hide() {
    autoSavePeriodLabel.setVisible(false);

    disconnect(autoSaveUpdater);
    autoSavePeriodSlider.setVisible(false);
    autoSavePeriodSlider.setEnabled(false);

    autoSavePeriodValueLabel.setVisible(false);

    languageLabel.setVisible(false);

    languageSelector.setVisible(false);
    languageSelector.setEnabled(false);
    disconnect(languageUpdater);

    inventoryTypeLabel.setVisible(false);

    inventoryTypeSelector.setVisible(false);
    inventoryTypeSelector.setEnabled(false);
    disconnect(inventoryTypeUpdater);
    inventoryTypeSelector.clear();

    fontLabel.setVisible(false);

    fontSetupButton.setVisible(false);
    fontSetupButton.setEnabled(false);

    colorThemeLabel.setVisible(false);

    colorThemeSelector.setVisible(false);
    colorThemeSelector.setEnabled(false);
    disconnect(colorThemeUpdater);
    colorThemeSelector.clear();

    eraseAllDataButton.setVisible(false);
    eraseAllDataButton.setEnabled(false);

    configFileLabel.setVisible(false);

    configFileSetupButton.setVisible(false);
    configFileSetupButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

SettingsMenu::~SettingsMenu() {

}
