#include "errorwidget.h"

ErrorWidget::ErrorWidget() :
        grid(QGridLayout(this)) {
    grid.addWidget(&errorLabel, 0, 0);
    errorLabel.setText("An unknown error occured!");
}

ErrorWidget::~ErrorWidget() {

}
