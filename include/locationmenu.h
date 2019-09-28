#ifndef INCLUDE_LOCATIONMENU_H_
#define INCLUDE_LOCATIONMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class Game;

class LocationMenu : public QObject {
private:
    Q_OBJECT
private:
    Game *game;
    bool displayed = false;
    QPushButton backButton;
    QComboBox locationSelector;
    QMetaObject::Connection locationUpdater;
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    LocationMenu(Game *game, QGridLayout *grid);
    ~LocationMenu();
    void display();
    void hide();
    bool isDisplayed() const;
};

#endif  // INCLUDE_LOCATIONMENU_H_
