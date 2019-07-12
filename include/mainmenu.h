#ifndef INCLUDE_MAINMENU_H_
#define INCLUDE_MAINMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QComboBox>

class MainWindow;

class MainMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QPushButton startButton,
                settingsButton,
                exitButton;
    QComboBox languageSelector;
    QGridLayout *grid;
    int cnt = 0;
private slots:
    void startFunction();
    void settingsFunction();
    void exitFunction();
public:
    MainMenu(MainWindow *w, QGridLayout *g);
    ~MainMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_MAINMENU_H_
