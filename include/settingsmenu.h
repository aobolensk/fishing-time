#ifndef INCLUDE_SETTINGSMENU_H_
#define INCLUDE_SETTINGSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>

class Game;

class SettingsMenu : public QObject {
private:
    Q_OBJECT
private:
    bool displayed = false;
    Game *game;
    QLabel autoSavePeriodLabel,
           languageLabel,
           inventoryTypeLabel,
           fontLabel,
           colorThemeLabel;
    QComboBox autoSavePeriodSelector,
              languageSelector,
              inventoryTypeSelector,
              colorThemeSelector;
    QPushButton fontSetupButton,
                eraseAllDataButton,
                backButton;
    QMetaObject::Connection languageUpdater,
                            autoSaveUpdater,
                            inventoryTypeUpdater,
                            colorThemeUpdater;
private:
    int autoSaveOptions[6] = {
        1, 3, 5, 10, 30, 60
    };
    QGridLayout *grid;
private slots:
    void fontSetupFunction();
    void eraseAllDataFunction();
    void backFunction();
public:
    SettingsMenu(Game *game, QGridLayout *grid);
    ~SettingsMenu();
    void display();
    void hide();
    bool isDisplayed() const;
    QString getSetting(const QString &settingName);
};

#endif  // INCLUDE_SETTINGSMENU_H_
