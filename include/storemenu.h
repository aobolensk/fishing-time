#ifndef INCLUDE_STOREMENU_H_
#define INCLUDE_STOREMENU_H_
#include <QPushButton>
#include <QGridLayout>

class MainWindow;

class StoreMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QPushButton backButton;
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    StoreMenu(MainWindow *w, QGridLayout *g);
    ~StoreMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_STOREMENU_H_
