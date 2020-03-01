#if defined(__GNUC__) && defined(__linux__)
#include <execinfo.h>
#endif
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QProcess>
#include <QSettings>
#include "aboutmenu.h"
#include "config.h"
#include "errorwidget.h"
#include "utils.h"

ErrorWidget::ErrorWidget() :
        grid(QGridLayout(this)),
        overlay(OverlayWidget(this)) {
    overlay.setText(
        "Fishing Time (development build)\n"
        "Version: " TOSTRING(COMMIT_HASH) "\n"
        "OS: " + AboutMenu::getSystemInfo() + "\n"
    );
    QSettings settings;
    if (!this->restoreGeometry(settings.value("errorWindowGeometry").toByteArray())) {
        this->setGeometry(QRect(QPoint(100, 200), QSize(640, 480)));
    }
    this->setWindowTitle("Fishing Time: Error");

    grid.addWidget(&errorLabel, 0, 0);
    QFont font = errorLabel.font();
    font.setPointSize(14);
    errorLabel.setFont(font);
    errorLabel.setText("An unknown error occurred!");
    errorLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    errorLabel.setWordWrap(true);

    grid.addWidget(&errorText, 1, 0);
    errorText.setReadOnly(true);
    errorText.stackUnder(&overlay);

    grid.addWidget(&exitButton, 2, 0);
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
    QSettings settings;
    settings.setValue("errorWindowGeometry", this->saveGeometry());
}

void ErrorWidget::setErrorLabel(const QString &text) {
    this->errorLabel.setText(text);
}

QString ErrorWidget::getErrorLabel() {
    return this->errorLabel.text();
}

void ErrorWidget::setErrorText(const QString &text) {
    this->errorText.setText(text);
}

QString ErrorWidget::getErrorText() {
    return this->errorText.toPlainText();
}

void ErrorWidget::signalHandler(int signum) {
    QFile errorLog("error.log");
    if (errorLog.open(QFile::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream f(&errorLog);
        #if _POSIX_C_SOURCE >= 200809L
        f << "Got signal: " << QString(strsignal(signum)) << endl;
        #else
        f << "Got signal: " << signum << endl;
        #endif  // __unix__
        f << getStacktrace();
        f << "-----------------------------------\n"
            "Version: " TOSTRING(COMMIT_HASH) "\n"
            "OS: " + AboutMenu::getSystemInfo() + "\n"
            "Compiler: " + AboutMenu::getCompilerInfo() + "\n";
        qApp->exit(1);
        QStringList newArgs = {
            "--err"
        };
        QProcess::startDetached(qApp->arguments()[0], newArgs);
    }
    exit(signum);
}

int ErrorWidget::launchViewer() {
    QFile errorLog("error.log");
    ErrorWidget error;
    if (errorLog.exists()) {
        errorLog.open(QIODevice::ReadOnly);
        QTextStream f(&errorLog);
        QString buffer;
        buffer = f.readLine();
        error.setErrorLabel(buffer);
        buffer = f.readAll();
        error.setErrorText(buffer);
    }
    error.show();
    return qApp->exec();
}
