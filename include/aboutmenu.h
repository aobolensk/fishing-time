#ifndef INCLUDE_ABOUTMENU_H_
#define INCLUDE_ABOUTMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class Game;

class AboutMenu : public QWidget {
private:
    Q_OBJECT
private:
    Game *game;
    QLabel descriptionLabel;
    QPushButton backButton;
    QGridLayout grid;
private slots:
    void backFunction();
public:
    AboutMenu(Game *game);
    ~AboutMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_ABOUTMENU_H_
