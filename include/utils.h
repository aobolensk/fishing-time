#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_
#include <QApplication>
#include "errorwidget.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

namespace FT_ERROR {
    extern ErrorWidget *error;
}

#define FT_ASSERT(expr, text)                               \
    if (!(expr)) {                                          \
        FT_ERROR::error = new ErrorWidget();                \
        FT_ERROR::error->setErrorText(                      \
            QStringLiteral("Assertion failed at "           \
            __FILE__ ":" TOSTRING(__LINE__) ": ") + text);  \
        qApp->exit(1);                                      \
    }                                                       \

#endif  // INCLUDE_UTILS_H_
