#ifndef INCLUDE_STOREMENU_H_
#define INCLUDE_STOREMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>

class MainWindow;

class StoreMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QLabel infoLabel;
    QLineEdit quantityText;
    QPushButton buyButton,
                backButton;
    QTableWidget storeTable;
    QGridLayout *grid;
private slots:
    void buyFunction();
    void backFunction();
private:
    void updateInfo();
    void updateTable();
public:
    StoreMenu(MainWindow *w, QGridLayout *g);
    ~StoreMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_STOREMENU_H_
