#ifndef INCLUDE_SETTINGSMENU_H_
#define INCLUDE_SETTINGSMENU_H_
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QPushButton>
#include <QSlider>
#include "menu.h"

class SettingsMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel autoSavePeriodLabel,
           autoSavePeriodValueLabel,
           languageLabel,
           inventoryTypeLabel,
           fontLabel,
           colorThemeLabel,
           loggerLevelLabel,
           configFileLabel,
           logFileLabel;
    QSlider autoSavePeriodSlider;
    QComboBox languageSelector,
              inventoryTypeSelector,
              colorThemeSelector,
              loggerLevelSelector;
    QPushButton fontSetupButton,
                eraseAllDataButton,
                configFileSetupButton,
                logFileSetupButton,
                backButton;
    QMetaObject::Connection languageUpdater,
                            autoSaveUpdater,
                            inventoryTypeUpdater,
                            colorThemeUpdater,
                            loggerLevelUpdater;
private:
private slots:
    void fontSetupFunction();
    void eraseAllDataFunction();
    void configFileSetupFunction();
    void logFileSetupFunction();
    void autoSavePeriodSliderFunction(int value);
    void backFunction() override;
public:
    SettingsMenu(Game *game, QGridLayout *grid);
    ~SettingsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_SETTINGSMENU_H_
