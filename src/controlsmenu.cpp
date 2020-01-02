#include "controlsmenu.h"
#include "game.h"

ControlsMenu::ControlsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&controlsTitleLabel, 0, 1);
    controlsTitleLabel.setVisible(false);
    controlsTitleLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    controlsTitleLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    for (size_t i = 0; i < (size_t)Controls::CONTROLS_N; ++i) {
        grid->addWidget(&controlsLabel[i], static_cast<int>(i + 1), 0);
        controlsLabel[i].setVisible(false);
        controlsLabel[i].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        grid->addWidget(&controlsText[i], static_cast<int>(i + 1), 1);
        controlsText[i].setVisible(false);
        controlsText[i].setReadOnly(true);

        grid->addWidget(&controlsButton[i], static_cast<int>(i + 1), 2);
        controlsButton[i].setVisible(false);
        controlsButton[i].setEnabled(false);

        grid->addWidget(&resetButton[i], static_cast<int>(i + 1), 3);
        resetButton[i].setVisible(false);
        resetButton[i].setEnabled(false);
    }

    grid->addWidget(&backButton, (size_t)Controls::CONTROLS_N + 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void ControlsMenu::setDefaults() {
    this->setDefault(Controls::HIDE_UI_ELEMENTS, 67108936); // Ctrl + H
    if (this->get(Controls::HIDE_UI_ELEMENTS) == 0) {
        this->set(Controls::HIDE_UI_ELEMENTS, 67108936); // Ctrl + H
    }
    this->setDefault(Controls::TOGGLE_FULLSCREEN_MODE, 16777274); // F11
    if (this->get(Controls::TOGGLE_FULLSCREEN_MODE) == 0) {
        this->set(Controls::TOGGLE_FULLSCREEN_MODE, 16777274); // F11
    }
    this->setDefault(Controls::GO_TO_PREVIOUS_MENU, 16777216); // Esc
    if (this->get(Controls::GO_TO_PREVIOUS_MENU) == 0) {
        this->set(Controls::GO_TO_PREVIOUS_MENU, 16777216); // Esc
    }
    this->setDefault(Controls::EXIT_FROM_THE_GAME, 67108945); // Ctrl + Q
    if (this->get(Controls::EXIT_FROM_THE_GAME) == 0) {
        this->set(Controls::EXIT_FROM_THE_GAME, 67108945); // Ctrl + Q
    }
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
        case Controls::EXIT_FROM_THE_GAME:
            controlsLabel[i].setText(game->str.exitFromTheGame);
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

        controlsButton[i].setText(game->str.edit);
        controlsButton[i].setVisible(true);
        controlsButton[i].setEnabled(true);
        connect(&controlsButton[i], static_cast<void(QPushButton::*)()>(&QPushButton::released),
            [this, i]() {
                if (currentControl != (Controls)i) {
                    if (currentControl != Controls::CONTROLS_N) {
                        controlsButton[(int)currentControl].setText(game->str.edit);
                    }
                    currentControl = (Controls)i;
                    controlsButton[i].setText(game->str.set);
                } else {
                    currentControl = Controls::CONTROLS_N;
                    controlsButton[i].setText(game->str.edit);
                }
            }
        );

        resetButton[i].setText(game->str.reset);
        resetButton[i].setVisible(true);
        resetButton[i].setEnabled(true);
        connect(&resetButton[i], static_cast<void(QPushButton::*)()>(&QPushButton::released),
            [this, i]() {
                controls[i] = defaultControls[i];
                controlsText[(size_t)i].setText(controls[i].toString(QKeySequence::NativeText));
                for (size_t j = 0; j < (size_t)Controls::CONTROLS_N; ++j) {
                    if (i == j) continue;
                    if (controls[j] == controls[i]) {
                        controls[j] = defaultControls[j];
                        QString keyText = controls[j].toString(QKeySequence::NativeText);
                        controlsText[j].setText(keyText);
                    }
                }
                if (currentControl != Controls::CONTROLS_N) {
                    controlsButton[(size_t)currentControl].setText(game->str.edit);
                    currentControl = Controls::CONTROLS_N;
                }
            }
        );
    }

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

QKeySequence ControlsMenu::getKeySequence(const QKeyEvent *const key) const {
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
            if (seq[0]) {
                bool set = true;
                for (size_t i = 0; i < (size_t)Controls::CONTROLS_N; ++i) {
                    if (i == (size_t)currentControl) continue;
                    if (seq == controls[i]) {
                        if (controls[i] == defaultControls[i]) {
                            set = false;
                        } else {
                            controls[i] = defaultControls[i];
                            QString keyText = controls[i].toString(QKeySequence::NativeText);
                            controlsText[i].setText(keyText);
                        }
                    }
                }
                if (set) {
                    QString keyText = seq.toString(QKeySequence::NativeText);
                    controls[(size_t)currentControl] = seq;
                    controlsText[(size_t)currentControl].setText(keyText);
                }
                controlsButton[(size_t)currentControl].setText(game->str.edit);
                currentControl = Controls::CONTROLS_N;
            }
        }
    }
    return Menu::eventFilter(obj, event);
}

QKeySequence ControlsMenu::get(Controls control) const {
    return controls[(size_t)control];
}

void ControlsMenu::setDefault(Controls control, int key) {
    defaultControls[(size_t)control] = QKeySequence(key);
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

        resetButton[i].setVisible(false);
        resetButton[i].setEnabled(false);
        resetButton[i].disconnect();
    }

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

ControlsMenu::~ControlsMenu() {

}
