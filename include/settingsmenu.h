#ifndef INCLUDE_SETTINGSMENU_H_
#define INCLUDE_SETTINGSMENU_H_
#include <QPushButton>
#include <QGridLayout>

class MainWindow;

class SettingsMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QPushButton backButton;
    QGridLayout *grid;
private slots:
    void backFunction();
public:
    SettingsMenu(MainWindow *w, QGridLayout *g);
    ~SettingsMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_SETTINGSMENU_H_
