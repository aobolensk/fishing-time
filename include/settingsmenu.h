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
           fontLabel;
    QComboBox autoSavePeriodSelector,
              languageSelector,
              inventoryTypeSelector;
    QPushButton fontSetupButton,
                backButton;
    QMetaObject::Connection autoSaveUpdater,
                            inventoryTypeUpdater;
    int autoSaveOptions[6] = {
        1, 3, 5, 10, 30, 60
    };
    QGridLayout *grid;
private slots:
    void fontSetupFunction();
    void backFunction();
public:
    SettingsMenu(Game *game, QGridLayout *grid);
    ~SettingsMenu();
    void display();
    void hide();
    bool isDisplayed() const;
};

#endif  // INCLUDE_SETTINGSMENU_H_
