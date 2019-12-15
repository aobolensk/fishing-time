#ifndef INCLUDE_CONTROLSMENU_H_
#define INCLUDE_CONTROLSMENU_H_
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "menu.h"

class ControlsMenu : public Menu {
private:
    Q_OBJECT
private:
    QString currentControl;
    QLabel hideUIElementsLabel;
    QLineEdit hideUIElementsText;
    QPushButton hideUIElementsButton,
                backButton;
    QKeySequence hideUIElementsControl;
private slots:
    void hideUIElementsEditFunction();
    void backFunction() override;
protected slots:
    bool eventFilter(QObject *obj, QEvent *event);
public:
    QKeySequence getKeySequence(const QKeyEvent *const key);
    QKeySequence getHideUIElementsControl();
public:
    ControlsMenu(Game *game, QGridLayout *grid);
    ~ControlsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_CONTROLSMENU_H_
