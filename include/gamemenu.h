#ifndef INCLUDE_GAMEMENU_H_
#define INCLUDE_GAMEMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QMutex>

class MainWindow;

class GameMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QPushButton clickButton,
                backButton,
                inventoryButton;
    QLabel infoLabel;
    QTableWidget table;
    QTableWidgetItem nameWidget,
                     quantityWidget;
    QMutex updateMutex;
    QGridLayout *grid;
private slots:
    void clickFunction();
    void backFunction();
    void inventoryFunction();
private:
    void updateInfo();
public:
    GameMenu(MainWindow *w, QGridLayout *g);
    ~GameMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_GAMEMENU_H_
