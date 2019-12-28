#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_
#include <QDebug>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define FT_ASSERT(expr, text)   \
    if (!(expr)) {              \
        qCritical() << text;    \
        exit(1);                \
    }                           \

#endif  // INCLUDE_UTILS_H_
