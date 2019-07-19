#include "settingsmenu.h"
#include "mainwindow.h"

SettingsMenu::SettingsMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    grid->addWidget(&autoSavePeriodLabel, 0, 0);
    autoSavePeriodLabel.setVisible(false);

    grid->addWidget(&autoSaveSelector, 0, 1);
    autoSaveSelector.setCurrentIndex(-1);
    autoSaveSelector.setVisible(false);
    autoSaveSelector.setEnabled(false);

    grid->addWidget(&languageLabel, 1, 0);
    languageLabel.setVisible(false);

    grid->addWidget(&languageSelector, 1, 1);
    for (int i = 0; i < window->str.languages.size(); ++i) {
        languageSelector.addItem(window->str.languages[i]);
    }
    qDebug() << (int)window->activeLanguage;
    connect(&languageSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this](int index){
            window->activeLanguage = (Language)index;
            window->str.setLanguage(window->activeLanguage);
            this->hide();
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
    autoSavePeriodLabel.setText(window->str.autoSavePeriod);
    autoSavePeriodLabel.setVisible(true);

    for (int i = 0; i < 6; ++i) {
        autoSaveSelector.addItem(QString::number(autoSaveOptions[i]) + ' ' + window->str.min);
    }
    autoSaveSelector.setVisible(true);
    autoSaveSelector.setEnabled(true);
    autoSaveSelector.setCurrentIndex(-1);
    int currentPeriod = window->autoSaveTimer.interval() / (60 * 1000);
    for (int i = 0; i < 6; ++i) {
        if (currentPeriod == autoSaveOptions[i]) {
            autoSaveSelector.setCurrentIndex(i);
            break;
        }
    }
    autoSaveUpdater = connect(&autoSaveSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
       [this](int index){ window->setAutoSavePeriod(autoSaveOptions[index]); });

    languageLabel.setText(window->str.language);
    languageLabel.setVisible(true);

    languageSelector.setCurrentIndex((int)window->activeLanguage);
    languageSelector.setVisible(true);
    languageSelector.setEnabled(true);

    backButton.setText(window->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void SettingsMenu::backFunction() {
    this->hide();
    window->mainMenu.display();
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
