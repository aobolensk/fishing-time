#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_
#include <QString>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

namespace FT_ERROR {
    void ft_assert[[noreturn]](QString place, QString text);
}

#ifndef FT_IGNORE_ASSERTS
#define FT_ASSERT(expr, text)                                       \
    if (!(expr)) {                                                  \
        FT_ERROR::ft_assert(__FILE__ ":" TOSTRING(__LINE__), text); \
    }
#else
#define FT_ASSERT(expr, text) ((void) (expr))
#endif  // FT_IGNORE_ASSERTS

namespace ft_utils {
    int toInt(const QKeySequence &obj);
}  // namespace ft_utils

#endif  // INCLUDE_UTILS_H_
