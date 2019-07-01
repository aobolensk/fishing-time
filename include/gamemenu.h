#ifndef INCLUDE_GAMEMENU_H_
#define INCLUDE_GAMEMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>

class MainWindow;

class GameMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QPushButton clickButton, backButton;
    QLabel infoLabel;
    QGridLayout *grid;
private slots:
    void clickFunction();
    void backFunction();
private:
    void updateInfo();
public:
    GameMenu(MainWindow *w, QGridLayout *g);
    ~GameMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_GAMEMENU_H_
