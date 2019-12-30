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
    QTextEdit errorText;
    QPushButton exitButton;
    OverlayWidget overlay;
private slots:
    void exitFunction();
public:
    ErrorWidget();
    ~ErrorWidget();
    void setErrorLabel(const QString &text);
    QString getErrorLabel();
    void setErrorText(const QString &text);
    QString getErrorText();
    static QString getStacktrace();
    static void signalHandler(int signum);
    static int launchViewer(int *argc, char***argv);
};

#endif  // INCLUDE_ERRORWIDGET_H_
