#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_
#include <QApplication>
#include "errorwidget.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

namespace FT_ERROR {
    void ft_assert(QString place, QString text);
}

#define FT_ASSERT(expr, text)                                       \
    if (!(expr)) {                                                  \
        FT_ERROR::ft_assert(__FILE__ ":" TOSTRING(__LINE__), text); \
    }                                                               \

#endif  // INCLUDE_UTILS_H_
