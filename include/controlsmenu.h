#ifndef INCLUDE_CONTROLSMENU_H_
#define INCLUDE_CONTROLSMENU_H_
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "config.h"
#include "menu.h"

class ControlsMenu : public Menu {
private:
    Q_OBJECT
private:
    Controls currentControl;
    QLabel controlsTitleLabel,
           controlsLabel[(size_t)Controls::CONTROLS_N];
    QLineEdit controlsText[(size_t)Controls::CONTROLS_N];
    QPushButton controlsButton[(size_t)Controls::CONTROLS_N],
                resetButton[(size_t)Controls::CONTROLS_N],
                backButton;
private slots:
    void backFunction() override;
protected slots:
    bool eventFilter(QObject *obj, QEvent *event) override;
public:
    QKeySequence getKeySequence(const QKeyEvent *const key) const;
    void setDefaults();
    bool isInEditingMode();
public:
    ControlsMenu(Game *game, QGridLayout *grid);
    ~ControlsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_CONTROLSMENU_H_
