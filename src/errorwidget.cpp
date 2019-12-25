#include "errorwidget.h"
#include "utils.h"

ErrorWidget::ErrorWidget() :
        grid(QGridLayout(this)),
        overlay(OverlayWidget(this)) {
    overlay.setText(
        "Fishing Time (development build)\n"
        "Version: " TOSTRING(COMMIT_HASH) "\n"
        "OS: " +
        QSysInfo::prettyProductName() + " " +
        QSysInfo::kernelType() + " " +
        QSysInfo::kernelVersion() + " " +
        QSysInfo::currentCpuArchitecture() +
        "\n"
    );
    this->setGeometry(100, 200, 640, 480);
    this->setFixedSize(this->width(), this->height());
    grid.addWidget(&errorLabel, 0, 0);
    QFont font = errorLabel.font();
    font.setPointSize(14);
    errorLabel.setFont(font);
    errorLabel.setText("An unknown error occured!");
    errorLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
}

ErrorWidget::~ErrorWidget() {

}
