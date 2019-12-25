#ifndef INCLUDE_ERRORWIDGET_H_
#define INCLUDE_ERRORWIDGET_H_
#include <QGridLayout>
#include <QLabel>
#include "menu.h"

class ErrorWidget : public QWidget {
private:
    Q_OBJECT
private:
    QGridLayout grid;
    QLabel errorLabel;
public:
    ErrorWidget();
    ~ErrorWidget();
};

#endif  // INCLUDE_ERRORWIDGET_H_
