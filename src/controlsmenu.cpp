#include "controlsmenu.h"
#include "game.h"
#include "utils.h"

ControlsMenu::ControlsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&controlsTitleLabel, 0, 1);
    controlsTitleLabel.setVisible(false);
    controlsTitleLabel.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    controlsTitleLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    for (size_t i = 0; i < static_cast<size_t>(Controls::CONTROLS_N); ++i) {
        grid->addWidget(&controlsLabel[i], static_cast<int>(i + 1), 0);
        controlsLabel[i].setVisible(false);
        controlsLabel[i].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        grid->addWidget(&controlsText[i], static_cast<int>(i + 1), 1);
        controlsText[i].setVisible(false);
        controlsText[i].setReadOnly(true);
        controlsText[i].setFocusPolicy(Qt::NoFocus);
        controlsText[i].setEnabled(false);

        grid->addWidget(&controlsButton[i], static_cast<int>(i + 1), 2);
        controlsButton[i].setVisible(false);
        controlsButton[i].setEnabled(false);

        grid->addWidget(&resetButton[i], static_cast<int>(i + 1), 3);
        resetButton[i].setVisible(false);
        resetButton[i].setEnabled(false);
    }

    grid->addWidget(&backButton, static_cast<size_t>(Controls::CONTROLS_N) + 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void ControlsMenu::display() {
    this->pre_display();

    currentControl = Controls::CONTROLS_N;

    controlsTitleLabel.setText(game->str.controls);
    controlsTitleLabel.setVisible(true);

    for (size_t i = 0; i < static_cast<size_t>(Controls::CONTROLS_N); ++i) {
        switch (static_cast<Controls>(i)) {
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
            this->game->cfg.controls[i].toString(QKeySequence::NativeText)
        );
        controlsText[i].setVisible(true);

        controlsButton[i].setText(game->str.edit);
        controlsButton[i].setVisible(true);
        controlsButton[i].setEnabled(true);
        connect(&controlsButton[i], static_cast<void(QPushButton::*)()>(&QPushButton::released),
            [this, i]() {
                if (currentControl != static_cast<Controls>(i)) {
                    if (currentControl != Controls::CONTROLS_N) {
                        controlsButton[static_cast<int>(currentControl)].setText(game->str.edit);
                    }
                    currentControl = static_cast<Controls>(i);
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
                game->cfg.controls[i] = game->cfg.defaultControls[i];
                controlsText[static_cast<size_t>(i)].setText(game->cfg.controls[i].toString(QKeySequence::NativeText));
                for (size_t j = 0; j < static_cast<size_t>(Controls::CONTROLS_N); ++j) {
                    if (i == j) continue;
                    if (game->cfg.controls[j] == game->cfg.controls[i]) {
                        game->cfg.controls[j] = game->cfg.defaultControls[j];
                        QString keyText = game->cfg.controls[j].toString(QKeySequence::NativeText);
                        controlsText[j].setText(keyText);
                    }
                }
                if (currentControl != Controls::CONTROLS_N) {
                    controlsButton[static_cast<size_t>(currentControl)].setText(game->str.edit);
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
            if (ft_utils::toInt(seq)) {
                bool set = true;
                for (size_t i = 0; i < static_cast<size_t>(Controls::CONTROLS_N); ++i) {
                    if (i == static_cast<size_t>(currentControl)) continue;
                    if (seq == game->cfg.controls[i]) {
                        if (game->cfg.controls[i] == game->cfg.defaultControls[i]) {
                            set = false;
                        } else {
                            game->cfg.controls[i] = game->cfg.defaultControls[i];
                            QString keyText = game->cfg.controls[i].toString(QKeySequence::NativeText);
                            controlsText[i].setText(keyText);
                        }
                    }
                }
                if (set) {
                    QString keyText = seq.toString(QKeySequence::NativeText);
                    game->cfg.controls[static_cast<size_t>(currentControl)] = seq;
                    controlsText[static_cast<size_t>(currentControl)].setText(keyText);
                }
                controlsButton[static_cast<size_t>(currentControl)].setText(game->str.edit);
                currentControl = Controls::CONTROLS_N;
            }
            return false;
        }
    }
    return Menu::eventFilter(obj, event);
}

void ControlsMenu::backFunction() {
    this->hide();
    game->settingsMenu.display();
}

bool ControlsMenu::isInEditingMode() {
    return currentControl != Controls::CONTROLS_N;
}

void ControlsMenu::hide() {
    this->pre_hide();

    controlsTitleLabel.setVisible(false);

    for (size_t i = 0; i < static_cast<size_t>(Controls::CONTROLS_N); ++i) {
        controlsLabel[i].setVisible(false);

        controlsText[i].setVisible(false);

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
