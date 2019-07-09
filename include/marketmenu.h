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
    static const int SELLERS_COUNT = 3;
    MainWindow *window;
    QPushButton backButton,
                dialogButton[SELLERS_COUNT];
    QLabel dialogLabel[SELLERS_COUNT];
    QString goodId[SELLERS_COUNT];
    qint64 goodPrice[SELLERS_COUNT];
    QGridLayout *grid;
private slots:
    void backFunction();
private:
    void updateDeals();
    void updateInfo();
public:
    MarketMenu(MainWindow *w, QGridLayout *g);
    ~MarketMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_MARKETMENU_H_
