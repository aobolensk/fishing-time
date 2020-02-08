#ifndef INCLUDE_ABOUTMENU_H_
#define INCLUDE_ABOUTMENU_H_
#include <QLabel>
#include <QPushButton>
#include "menu.h"

class AboutMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel descriptionLabel;
    QPushButton backButton;
private slots:
    void backFunction() override;
public:
    AboutMenu(Game *game);
    ~AboutMenu() override;
    void display() override;
    void hide() override;
    QString getAboutInfo();
    static QString getSystemInfo();
    static QString getCompilerInfo();
};

#endif  // INCLUDE_ABOUTMENU_H_
