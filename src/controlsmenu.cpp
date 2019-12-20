#include "controlsmenu.h"
#include "game.h"

ControlsMenu::ControlsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&controlsTitleLabel, 0, 1);
    controlsTitleLabel.setVisible(false);
    controlsTitleLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    controlsTitleLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    for (size_t i = 0; i < (size_t)Controls::CONTROLS_N; ++i) {
        grid->addWidget(&controlsLabel[i], i + 1, 0);
        controlsLabel[i].setVisible(false);
        controlsLabel[i].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        grid->addWidget(&controlsText[i], i + 1, 1);
        controlsText[i].setVisible(false);
        controlsText[i].setReadOnly(true);

        grid->addWidget(&controlsButton[i], i + 1, 2);
        controlsButton[i].setText(game->str.edit);
        controlsButton[i].setVisible(false);
        controlsButton[i].setEnabled(false);
    }

    grid->addWidget(&backButton, (size_t)Controls::CONTROLS_N + 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void ControlsMenu::display() {
    this->pre_display();

    currentControl = Controls::CONTROLS_N;

    controlsTitleLabel.setText(game->str.controls);
    controlsTitleLabel.setVisible(true);

    for (size_t i = 0; i < (size_t)Controls::CONTROLS_N; ++i) {
        switch ((Controls)i) {
        case Controls::HIDE_UI_ELEMENTS:
            controlsLabel[i].setText(game->str.hideUIElements);
            break;
        case Controls::TOGGLE_FULLSCREEN_MODE:
            controlsLabel[i].setText(game->str.toggleFullscreenMode);
            break;
        case Controls::GO_TO_PREVIOUS_MENU:
            controlsLabel[i].setText(game->str.goToPreviousMenu);
            break;
        case Controls::CONTROLS_N:
            break;
        }
        controlsLabel[i].setVisible(true);

        controlsText[i].setText(
            this->controls[i].toString(QKeySequence::NativeText)
        );
        controlsText[i].setVisible(true);
        controlsText[i].setEnabled(true);

        controlsButton[i].setVisible(true);
        controlsButton[i].setEnabled(true);

        connect(&controlsButton[i], static_cast<void(QPushButton::*)()>(&QPushButton::released),
            [this, i]() {
                if (currentControl != (Controls)i) {
                    currentControl = (Controls)i;
                    controlsButton[i].setText(game->str.set);
                } else {
                    currentControl = Controls::CONTROLS_N;
                    controlsButton[i].setText(game->str.edit);
                }
            }
        );
    }

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

QKeySequence ControlsMenu::getKeySequence(const QKeyEvent *const key) {
    int keyInt = key->key();
    Qt::Key keyCode = static_cast<Qt::Key>(keyInt);
    if (keyCode == Qt::Key_Control ||
        keyCode == Qt::Key_Shift ||
        keyCode == Qt::Key_Alt ||
        keyCode == Qt::Key_Meta) {
        return false;
    }
    Qt::KeyboardModifiers modifiers = key->modifiers();
    if(modifiers & Qt::ShiftModifier)
        keyInt += Qt::SHIFT;
    if(modifiers & Qt::ControlModifier)
        keyInt += Qt::CTRL;
    if(modifiers & Qt::AltModifier)
        keyInt += Qt::ALT;
    if(modifiers & Qt::MetaModifier)
        keyInt += Qt::META;
    return QKeySequence(keyInt);
}

bool ControlsMenu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        if (currentControl != Controls::CONTROLS_N) {
            QKeyEvent *key = static_cast<QKeyEvent *>(event);
            QKeySequence seq = getKeySequence(key);
            QString keyText = seq.toString(QKeySequence::NativeText);
            controls[(size_t)currentControl] = seq;
            controlsText[(size_t)currentControl].setText(keyText);
            if (seq[0]) {
                controlsButton[(size_t)currentControl].setText(game->str.edit);
                currentControl = Controls::CONTROLS_N;
            }
        }
    }
    return Menu::eventFilter(obj, event);
}

QKeySequence ControlsMenu::get(Controls control) {
    return controls[(size_t)control];
}

void ControlsMenu::set(Controls control, int key) {
    controls[(size_t)control] = QKeySequence(key);
}

void ControlsMenu::backFunction() {
    this->hide();
    game->settingsMenu.display();
}

void ControlsMenu::hide() {
    this->pre_hide();

    controlsTitleLabel.setVisible(false);

    for (size_t i = 0; i < (size_t)Controls::CONTROLS_N; ++i) {
        controlsLabel[i].setVisible(false);

        controlsText[i].setVisible(false);
        controlsText[i].setEnabled(false);

        controlsButton[i].setVisible(false);
        controlsButton[i].setEnabled(false);
        controlsButton[i].disconnect();
    }

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

ControlsMenu::~ControlsMenu() {

}
