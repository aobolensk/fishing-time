#ifndef INCLUDE_LOGINMENU_H_
#define INCLUDE_LOGINMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>

class MainWindow;

class LoginMenu : public QObject {
private:
    Q_OBJECT
private:
    MainWindow *window;
    QLineEdit loginText;
    QPushButton loginButton,
                signUpButton,
                backButton;
    QGridLayout *grid;
private slots:
    void loginFunction();
    void signUpFunction();
    void backFunction();
public:
    LoginMenu(MainWindow *w, QGridLayout *g);
    ~LoginMenu();
    void display();
    void hide();
};

#endif  // INCLUDE_LOGINMENU_H_
