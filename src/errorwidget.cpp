#if defined(__GNUC__) && defined(__linux__)
#include <execinfo.h>
#endif
#include <QApplication>
#include <QDebug>
#include "config.h"
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

    #ifdef STACKTRACE_AVAILABLE
    grid.addWidget(&stacktraceLabel, 1, 0);
    stacktraceLabel.setText("Stacktrace:");
    stacktraceLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QString stacktrace = getStacktrace();

    grid.addWidget(&stacktraceText, 2, 0);
    stacktraceText.setReadOnly(true);
    stacktraceText.setText(stacktrace);

    qDebug().noquote() << stacktrace;
    #endif

    grid.addWidget(&exitButton, 3, 0);
    exitButton.setText("Exit");
    connect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));
}

void ErrorWidget::exitFunction() {
    QApplication::exit();
}

QString ErrorWidget::getStacktrace() {
    QString result;
    #ifdef STACKTRACE_AVAILABLE
    void *buffer[Config::STACKTRACE_SIZE];
    int size = backtrace(buffer, Config::STACKTRACE_SIZE);
    char **symbols = backtrace_symbols(buffer, size);
    for (int i = 1; i < size; ++i) {
        result += QString(symbols[i]) + '\n';
    }
    free(symbols);
    #endif
    return result;
}

ErrorWidget::~ErrorWidget() {

}

void ErrorWidget::setErrorText(const QString &text) {
    return this->errorLabel.setText(text);
}

QString ErrorWidget::getErrorText() {
    return this->errorLabel.text();
}

void ErrorWidget::signalHandler(int signum) {
    ErrorWidget error;
    error.setErrorText(error.getErrorText() + "\nReceived \"" + strsignal(signum) + "\" signal");
    error.show();
    QApplication::exec();
    exit(signum);
}
