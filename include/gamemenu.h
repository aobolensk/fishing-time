#ifndef INCLUDE_GAMEMENU_H_
#define INCLUDE_GAMEMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>

class MainWindow;

class GameMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QPushButton clickButton,
                backButton,
                inventoryButton,
                marketButton;
    QLabel infoLabel;
    QTableWidget table;
    QTableWidgetItem nameWidget,
                     quantityWidget;
    QGridLayout *grid;
private slots:
    void clickFunction();
    void backFunction();
    void inventoryFunction();
    void marketFunction();
private:
    void updateInfo();
public:
    void updateInventoryTable();
public:
    GameMenu(MainWindow *w, QGridLayout *g);
    ~GameMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_GAMEMENU_H_
