#include <QKeyEvent>
#include <QDebug>
#include "menu.h"

bool Menu::isDisplayed() const {
    return displayed;
}

bool Menu::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        qDebug() << typeid(*this).name() << "->" << key->key();
        if (key->key() == 16777216) { // escape
            this->backFunction();
        }
    }
    return QObject::eventFilter(obj, event);
}

void Menu::backFunction() {

}
