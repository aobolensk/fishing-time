#ifndef INCLUDE_ERRORWIDGET_H_
#define INCLUDE_ERRORWIDGET_H_
#include <QGridLayout>
#include <QLabel>
#include "overlaywidget.h"

class ErrorWidget : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout grid;
    QLabel errorLabel;
    OverlayWidget overlay;
public:
    ErrorWidget();
    ~ErrorWidget();
    static QString getStacktrace();
};

#endif  // INCLUDE_ERRORWIDGET_H_
