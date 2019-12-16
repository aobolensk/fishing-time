#include "controlsmenu.h"
#include "game.h"

ControlsMenu::ControlsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {
    grid->addWidget(&controlsLabel, 0, 1);
    controlsLabel.setVisible(false);

    grid->addWidget(&hideUIElementsLabel, 1, 0);
    hideUIElementsLabel.setVisible(false);

    grid->addWidget(&hideUIElementsText, 1, 1);
    hideUIElementsText.setVisible(false);
    hideUIElementsText.setReadOnly(true);

    grid->addWidget(&hideUIElementsButton, 1, 2);
    hideUIElementsButton.setVisible(false);
    hideUIElementsButton.setEnabled(false);
    connect(&hideUIElementsButton, SIGNAL(released()), this, SLOT(hideUIElementsEditFunction()));

    grid->addWidget(&toggleFullscreenModeLabel, 2, 0);
    toggleFullscreenModeLabel.setVisible(false);

    grid->addWidget(&toggleFullscreenModeText, 2, 1);
    toggleFullscreenModeText.setVisible(false);
    toggleFullscreenModeText.setReadOnly(true);

    grid->addWidget(&toggleFullscreenModeButton, 2, 2);
    toggleFullscreenModeButton.setVisible(false);
    toggleFullscreenModeButton.setEnabled(false);
    connect(&toggleFullscreenModeButton, SIGNAL(released()), this, SLOT(toggleFullscreenModeEditFunction()));

    grid->addWidget(&backButton, 10, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void ControlsMenu::display() {
    this->pre_display();

    controlsLabel.setText(game->str.controls);
    controlsLabel.setVisible(true);

    hideUIElementsLabel.setText(game->str.hideUIElements);
    hideUIElementsLabel.setVisible(true);

    hideUIElementsText.setText(
        this->hideUIElementsControl.toString(QKeySequence::NativeText)
    );
    hideUIElementsText.setVisible(true);
    hideUIElementsText.setEnabled(true);

    hideUIElementsButton.setText(game->str.edit);
    hideUIElementsButton.setVisible(true);
    hideUIElementsButton.setEnabled(true);

    toggleFullscreenModeLabel.setText(game->str.toggleFullscreenMode);
    toggleFullscreenModeLabel.setVisible(true);

    toggleFullscreenModeText.setText(
        this->toggleFullscreenModeControl.toString(QKeySequence::NativeText)
    );
    toggleFullscreenModeText.setVisible(true);
    toggleFullscreenModeText.setEnabled(true);

    toggleFullscreenModeButton.setText(game->str.edit);
    toggleFullscreenModeButton.setVisible(true);
    toggleFullscreenModeButton.setEnabled(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);

    displayed = true;
}

void ControlsMenu::hideUIElementsEditFunction() {
    if (currentControl != "hideUIElements") {
        currentControl = "hideUIElements";
        hideUIElementsButton.setText(game->str.set);
    } else {
        currentControl = "";
        hideUIElementsButton.setText(game->str.edit);
    }
}

void ControlsMenu::toggleFullscreenModeEditFunction() {
    if (currentControl != "toggleFullscreenMode") {
        currentControl = "toggleFullscreenMode";
        toggleFullscreenModeButton.setText(game->str.set);
    } else {
        currentControl = "";
        toggleFullscreenModeButton.setText(game->str.edit);
    }
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
        if (currentControl.size() > 0) {
            QKeyEvent *key = static_cast<QKeyEvent *>(event);
            QKeySequence seq = getKeySequence(key);
            QString keyText = seq.toString(QKeySequence::NativeText);

            if (currentControl == "hideUIElements") {
                hideUIElementsControl = seq;
                hideUIElementsText.setText(keyText);
            }
        }
    }
    return Menu::eventFilter(obj, event);
}

void ControlsMenu::backFunction() {
    this->hide();
    game->settingsMenu.display();
}

void ControlsMenu::setHideUIElementsControl(int key) {
    hideUIElementsControl = QKeySequence(key);
}

QKeySequence ControlsMenu::getHideUIElementsControl() {
    return hideUIElementsControl;
}

void ControlsMenu::setToggleFullscreenModeControl(int key) {
    toggleFullscreenModeControl = QKeySequence(key);
}

QKeySequence ControlsMenu::getToggleFullscreenModeControl() {
    return toggleFullscreenModeControl;
}

void ControlsMenu::hide() {
    this->pre_hide();

    controlsLabel.setVisible(false);

    hideUIElementsLabel.setVisible(false);

    hideUIElementsText.setVisible(false);
    hideUIElementsText.setEnabled(false);

    hideUIElementsButton.setVisible(false);
    hideUIElementsButton.setEnabled(false);

    toggleFullscreenModeLabel.setVisible(false);

    toggleFullscreenModeText.setVisible(false);
    toggleFullscreenModeText.setEnabled(false);

    toggleFullscreenModeButton.setVisible(false);
    toggleFullscreenModeButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

ControlsMenu::~ControlsMenu() {

}
