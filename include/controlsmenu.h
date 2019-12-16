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
    QLabel controlsLabel,
           hideUIElementsLabel,
           toggleFullscreenModeLabel;
    QLineEdit hideUIElementsText,
              toggleFullscreenModeText;
    QPushButton hideUIElementsButton,
                toggleFullscreenModeButton,
                backButton;
    QKeySequence hideUIElementsControl,
                 toggleFullscreenModeControl;
private slots:
    void hideUIElementsEditFunction();
    void toggleFullscreenModeEditFunction();
    void backFunction() override;
protected slots:
    bool eventFilter(QObject *obj, QEvent *event) override;
public:
    QKeySequence getKeySequence(const QKeyEvent *const key);
    void setHideUIElementsControl(int key);
    QKeySequence getHideUIElementsControl();
    void setToggleFullscreenModeControl(int key);
    QKeySequence getToggleFullscreenModeControl();
public:
    ControlsMenu(Game *game, QGridLayout *grid);
    ~ControlsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_CONTROLSMENU_H_
