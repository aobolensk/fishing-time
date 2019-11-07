#ifndef INCLUDE_ABOUTMENU_H_
#define INCLUDE_ABOUTMENU_H_
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include "menu.h"

class AboutMenu : public Menu {
private:
    Q_OBJECT
private:
    QLabel descriptionLabel;
    QPushButton backButton;
private slots:
    void backFunction();
public:
    AboutMenu(Game *game);
    ~AboutMenu();
    void display() override;
    void hide() override;
    QString getAboutInfo();
};

#endif  // INCLUDE_ABOUTMENU_H_
