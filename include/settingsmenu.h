#ifndef INCLUDE_SETTINGSMENU_H_
#define INCLUDE_SETTINGSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSlider>
#include "menu.h"

class SettingsMenu : public Menu {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel autoSavePeriodLabel,
           autoSavePeriodValueLabel,
           languageLabel,
           inventoryTypeLabel,
           fontLabel,
           colorThemeLabel,
           configFileLabel;
    QSlider autoSavePeriodSlider;
    QComboBox languageSelector,
              inventoryTypeSelector,
              colorThemeSelector;
    QPushButton fontSetupButton,
                eraseAllDataButton,
                configFileSetupButton,
                backButton;
    QMetaObject::Connection languageUpdater,
                            autoSaveUpdater,
                            inventoryTypeUpdater,
                            colorThemeUpdater;
private:
    QGridLayout *grid;
private slots:
    void fontSetupFunction();
    void eraseAllDataFunction();
    void configFileSetupFunction();
    void autoSavePeriodSliderFunction(int value);
    void backFunction();
public:
    SettingsMenu(Game *game, QGridLayout *grid);
    ~SettingsMenu();
    void display() override;
    void hide() override;
    QString getSetting(const QString &settingName);
};

#endif  // INCLUDE_SETTINGSMENU_H_
