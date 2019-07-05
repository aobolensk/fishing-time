#ifndef INCLUDE_MARKETMENU_H_
#define INCLUDE_MARKETMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>

class MainWindow;

class MarketMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QPushButton backButton,
                dialog1Button,
                dialog2Button,
                dialog3Button;
    QGridLayout *grid;
private slots:
    void backFunction();
private:
    void updateInfo();
public:
    MarketMenu(MainWindow *w, QGridLayout *g);
    ~MarketMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_MARKETMENU_H_
