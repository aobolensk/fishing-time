#include "controlsmenu.h"
#include "game.h"

ControlsMenu::ControlsMenu(Game *game, QGridLayout *grid) :
        Menu(game, grid) {

    grid->addWidget(&hideUIElementsLabel, 1, 0);
    hideUIElementsLabel.setVisible(false);
    hideUIElementsLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    grid->addWidget(&hideUIElementsText, 1, 1);
    hideUIElementsText.setVisible(false);
    hideUIElementsText.setReadOnly(true);

    grid->addWidget(&hideUIElementsButton, 1, 2);
    hideUIElementsButton.setVisible(false);
    hideUIElementsButton.setEnabled(false);
    connect(&hideUIElementsButton, SIGNAL(released()), this, SLOT(hideUIElementsEditFunction()));

    grid->addWidget(&backButton, 2, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

void ControlsMenu::display() {
    this->pre_display();

    hideUIElementsLabel.setText(game->str.hideUIElements);
    hideUIElementsLabel.setVisible(true);

    hideUIElementsText.setVisible(true);
    hideUIElementsText.setEnabled(true);

    hideUIElementsButton.setText(game->str.edit);
    hideUIElementsButton.setVisible(true);
    hideUIElementsButton.setEnabled(true);

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

QKeySequence ControlsMenu::getHideUIElementsControl() {
    return hideUIElementsControl;
}

void ControlsMenu::hide() {
    this->pre_hide();

    hideUIElementsLabel.setVisible(false);

    hideUIElementsText.setVisible(false);
    hideUIElementsText.setEnabled(false);

    hideUIElementsButton.setVisible(false);
    hideUIElementsButton.setEnabled(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);

    displayed = false;
}

ControlsMenu::~ControlsMenu() {

}
