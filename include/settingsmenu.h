#ifndef INCLUDE_SETTINGSMENU_H_
#define INCLUDE_SETTINGSMENU_H_
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include "menu.h"

class SettingsMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel languageLabel,
           autoSavePeriodLabel,
           autoSavePeriodValueLabel,
           loggerLevelLabel,
           configFileLabel,
           logFileLabel;
    QSlider autoSavePeriodSlider;
    QComboBox languageSelector,
              loggerLevelSelector;
    QPushButton controlsButton,
                appearanceButton,
                eraseAllDataButton,
                configFileSetupButton,
                logFileSetupButton,
                backButton;
    QMetaObject::Connection languageUpdater,
                            autoSaveUpdater,
                            loggerLevelUpdater;
private slots:
    void eraseAllDataFunction();
    void configFileSetupFunction();
    void logFileSetupFunction();
    void autoSavePeriodSliderFunction(int value);
    void controlsFunction();
    void appearanceFunction();
    void backFunction() override;
public:
    SettingsMenu(Game *game, QGridLayout *grid);
    ~SettingsMenu() override;
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_SETTINGSMENU_H_
