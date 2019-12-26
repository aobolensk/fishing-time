#ifndef INCLUDE_ERRORWIDGET_H_
#define INCLUDE_ERRORWIDGET_H_
#include <QGridLayout>
#include <QLabel>
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
    OverlayWidget overlay;
public:
    ErrorWidget();
    ~ErrorWidget();
    static QString getStacktrace();
};

#endif  // INCLUDE_ERRORWIDGET_H_
