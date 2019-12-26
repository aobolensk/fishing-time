#ifndef INCLUDE_ERRORWIDGET_H_
#define INCLUDE_ERRORWIDGET_H_
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include "overlaywidget.h"

#if defined(__GNUC__) && defined(__linux__)
#define STACKTRACE_AVAILABLE
#endif

class ErrorWidget : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout grid;
    QLabel errorLabel;
    #ifdef STACKTRACE_AVAILABLE
    QLabel stacktraceLabel;
    QTextEdit stacktraceText;
    #endif
    QPushButton exitButton;
    OverlayWidget overlay;
private slots:
    void exitFunction();
public:
    ErrorWidget();
    ~ErrorWidget();
    static QString getStacktrace();
    static void signalHandler(int signum);
};

#endif  // INCLUDE_ERRORWIDGET_H_
