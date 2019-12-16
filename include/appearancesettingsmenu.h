#ifndef INCLUDE_APPEARANCESETTINGSMENU_H_
#define INCLUDE_APPEARANCESETTINGSMENU_H_
#include <QCheckBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "menu.h"

class AppearanceSettingsMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel appearanceSettingsLabel,
           inventoryTypeLabel,
           fontLabel,
           colorThemeLabel,
           backgroundImagesLabel;
    QComboBox inventoryTypeSelector,
              colorThemeSelector;
    QPushButton fontSetupButton,
                backButton;
    QCheckBox backgroundImagesSwitch;
    QMetaObject::Connection languageUpdater,
                            autoSaveUpdater,
                            inventoryTypeUpdater,
                            colorThemeUpdater,
                            backgroundImagesUpdater,
                            loggerLevelUpdater;
private slots:
    void fontSetupFunction();
    void backFunction() override;
public:
    AppearanceSettingsMenu(Game *game, QGridLayout *grid);
    ~AppearanceSettingsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_APPEARANCESETTINGSMENU_H_
