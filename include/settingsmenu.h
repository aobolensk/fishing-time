#ifndef INCLUDE_SETTINGSMENU_H_
#define INCLUDE_SETTINGSMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>

class Game;

class SettingsMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    QPushButton backButton;
    QLabel autoSavePeriodLabel,
           languageLabel;
    QComboBox autoSaveSelector,
              languageSelector;
    QMetaObject::Connection autoSaveUpdater;
    int autoSaveOptions[6] = {
        1, 3, 5, 10, 30, 60
    };
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    SettingsMenu(Game *game, QGridLayout *grid);
    ~SettingsMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_SETTINGSMENU_H_
