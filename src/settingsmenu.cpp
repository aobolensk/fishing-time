#include <QFileDialog>
#include <QMessageBox>
#include "settingsmenu.h"
#include "game.h"

SettingsMenu::SettingsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&appearanceButton, 0, 1);
    appearanceButton.setVisible(false);
    appearanceButton.setEnabled(false);
    connect(&appearanceButton, SIGNAL(released()), this, SLOT(appearanceFunction()));

    grid->addWidget(&controlsButton, 1, 1);
    controlsButton.setVisible(false);
    controlsButton.setEnabled(false);
    connect(&controlsButton, SIGNAL(released()), this, SLOT(controlsFunction()));

    grid->addWidget(&languageLabel, 2, 0);
    languageLabel.setVisible(false);
    languageLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&languageSelector, 2, 1);
    for (int i = 0; i < game->str.languages.size(); ++i) {
        languageSelector.addItem(game->str.languages[static_cast<Language>(i)].first + " (" +
            QString::number(game->str.getNumberOfEntries(static_cast<Language>(i))) + "/" +
            QString::number(game->str.getTotalNumberOfEntries()) + " -> " +
            QString::number(game->str.getReadiness(static_cast<Language>(i))) + "%) ready");
    }
    languageSelector.setVisible(false);
    languageSelector.setEnabled(false);

    grid->addWidget(&autoSavePeriodLabel, 3, 0);
    autoSavePeriodLabel.setVisible(false);
    autoSavePeriodLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&autoSavePeriodSlider, 3, 1);
    autoSavePeriodSlider.setOrientation(Qt::Horizontal);
    autoSavePeriodSlider.setRange(Config::MIN_AUTO_SAVE_PERIOD, Config::MAX_AUTO_SAVE_PERIOD);
    autoSavePeriodSlider.setVisible(false);
    autoSavePeriodSlider.setEnabled(false);

    grid->addWidget(&autoSavePeriodValueLabel, 3, 2);
    autoSavePeriodValueLabel.setVisible(false);

    grid->addWidget(&loggerLevelLabel, 4, 0);
    loggerLevelLabel.setVisible(false);
    loggerLevelLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&loggerLevelSelector, 4, 1);
    loggerLevelSelector.setCurrentIndex(-1);
    loggerLevelSelector.setVisible(false);
    loggerLevelSelector.setEnabled(false);

    grid->addWidget(&configFileLabel, 5, 0);
    configFileLabel.setVisible(false);
    configFileLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&configFileSetupButton, 5, 1);
    configFileSetupButton.setVisible(false);
    configFileSetupButton.setEnabled(false);
    connect(&configFileSetupButton, SIGNAL(released()), this, SLOT(configFileSetupFunction()));

    grid->addWidget(&logFileLabel, 6, 0);
    logFileLabel.setVisible(false);
    logFileLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&logFileSetupButton, 6, 1);
    logFileSetupButton.setVisible(false);
    logFileSetupButton.setEnabled(false);
    connect(&logFileSetupButton, SIGNAL(released()), this, SLOT(logFileSetupFunction()));

    grid->addWidget(&eraseAllDataButton, 7, 1);
    eraseAllDataButton.setVisible(false);
    eraseAllDataButton.setEnabled(false);
    connect(&eraseAllDataButton, SIGNAL(released()), this, SLOT(eraseAllDataFunction()));

    grid->addWidget(&backButton, 8, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void SettingsMenu::display() {
    this->pre_display();

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

    languageSelector.setCurrentIndex(static_cast<int>(game->activeLanguage));
    languageSelector.setVisible(true);
    languageSelector.setEnabled(true);
    languageUpdater = connect(&languageSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this](int index) {
            this->hide();
            this->game->str.setLanguage(this->game->activeLanguage = static_cast<Language>(index), game);
            this->display();
        });

    loggerLevelLabel.setText(game->str.loggerLevel);
    loggerLevelLabel.setVisible(true);

    loggerLevelSelector.addItem(game->str.loggerLevelRelease);
    loggerLevelSelector.addItem(game->str.loggerLevelDebug);
    loggerLevelSelector.setCurrentIndex(static_cast<int>(game->loggerLevel));
    loggerLevelSelector.setVisible(true);
    loggerLevelSelector.setEnabled(true);
    loggerLevelUpdater = connect(&loggerLevelSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
    [this](int index) {
        if (index != -1) {
            this->game->loggerLevel = static_cast<LoggerLevel>(index);
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

    logFileLabel.setText(game->str.logFile);
    logFileLabel.setVisible(true);

    logFileSetupButton.setText(game->str.open);
    logFileSetupButton.setVisible(true);
    logFileSetupButton.setEnabled(true);

    appearanceButton.setText(game->str.appearance);
    appearanceButton.setVisible(true);
    appearanceButton.setEnabled(true);

    controlsButton.setText(game->str.controls);
    controlsButton.setVisible(true);
    controlsButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void SettingsMenu::configFileSetupFunction() {
    QString config_file = QFileDialog::getOpenFileName();
    game->logger.info("New config file: " + config_file);
    if (config_file.size() > 0) {
        game->setConfigFile(config_file);
    }
}

void SettingsMenu::logFileSetupFunction() {
    QString log_file = QFileDialog::getOpenFileName();
    if (log_file.size() > 0) {
        game->logFile = log_file;
        game->logger.setFile(game->logFile);
    }
    game->logger.info("New log file: " + log_file);
}

void SettingsMenu::eraseAllDataFunction() {
    QMessageBox::StandardButton eraseResult =
        QMessageBox::question(nullptr, game->str.fishingTime, game->str.eraseAllDataConfirmation,
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::No);
    if (eraseResult == QMessageBox::Yes) {
        game->gameMenu.logOutFunction();
        if (remove(game->getConfigFileName().toStdString().c_str())) {
            game->logger.error("Error while deleting config file");
        } else {
            game->logger.info("Config file is successfully removed");
        }
    }
}

void SettingsMenu::autoSavePeriodSliderFunction(int value) {
    game->setAutoSavePeriod(value);
    autoSavePeriodValueLabel.setText(QString::number(value));
}

void SettingsMenu::appearanceFunction() {
    this->hide();
    game->appearanceSettingsMenu.display();
}

void SettingsMenu::controlsFunction() {
    this->hide();
    game->controlsMenu.display();
}

void SettingsMenu::backFunction() {
    this->hide();
    game->mainMenu.display();
}

void SettingsMenu::hide() {
    this->pre_hide();

    autoSavePeriodLabel.setVisible(false);

    disconnect(autoSaveUpdater);
    autoSavePeriodSlider.setVisible(false);
    autoSavePeriodSlider.setEnabled(false);

    autoSavePeriodValueLabel.setVisible(false);

    languageLabel.setVisible(false);

    languageSelector.setVisible(false);
    languageSelector.setEnabled(false);
    disconnect(languageUpdater);

    loggerLevelLabel.setVisible(false);

    loggerLevelSelector.setVisible(false);
    loggerLevelSelector.setEnabled(false);
    disconnect(loggerLevelUpdater);
    loggerLevelSelector.clear();

    eraseAllDataButton.setVisible(false);
    eraseAllDataButton.setEnabled(false);

    configFileLabel.setVisible(false);

    configFileSetupButton.setVisible(false);
    configFileSetupButton.setEnabled(false);

    logFileLabel.setVisible(false);

    logFileSetupButton.setVisible(false);
    logFileSetupButton.setEnabled(false);

    appearanceButton.setVisible(false);
    appearanceButton.setEnabled(false);

    controlsButton.setVisible(false);
    controlsButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

SettingsMenu::~SettingsMenu() {

}
