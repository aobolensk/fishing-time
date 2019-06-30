#ifndef INCLUDE_MAINMENU_H_
#define INCLUDE_MAINMENU_H_
#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>

class MainMenu : public QObject {
private:
    Q_OBJECT
private:
    QWidget *window;
    QPushButton clickButton, exitButton;
    QGridLayout *grid;
    int cnt = 0;
private slots:
    void clickFunction();
    void exitFunction();
public:
    MainMenu(QWidget *w, QGridLayout *g);
    ~MainMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_MAINMENU_H_
