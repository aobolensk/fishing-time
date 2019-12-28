#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_
#include <stdexcept>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define FT_ASSERT(expr, text)                                                   \
    if (!(expr)) {                                                              \
        throw std::runtime_error((text).toStdString());                         \
    }                                                                           \

#endif  // INCLUDE_UTILS_H_
