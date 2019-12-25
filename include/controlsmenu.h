#ifndef INCLUDE_CONTROLSMENU_H_
#define INCLUDE_CONTROLSMENU_H_
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "menu.h"

enum class Controls {
    HIDE_UI_ELEMENTS,
    TOGGLE_FULLSCREEN_MODE,
    GO_TO_PREVIOUS_MENU,
    CONTROLS_N
};

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
    QKeySequence defaultControls[(size_t)Controls::CONTROLS_N],
                 controls[(size_t)Controls::CONTROLS_N];
private slots:
    void backFunction() override;
protected slots:
    bool eventFilter(QObject *obj, QEvent *event) override;
public:
    QKeySequence getKeySequence(const QKeyEvent *const key) const;
    QKeySequence get(Controls control) const;
    void setDefault(Controls control, int key);
    void set(Controls control, int key);
    void setDefaults();
public:
    ControlsMenu(Game *game, QGridLayout *grid);
    ~ControlsMenu();
    void display() override;
    void hide() override;
};

#endif  // INCLUDE_CONTROLSMENU_H_
