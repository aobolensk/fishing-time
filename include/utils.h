#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

namespace FT_ERROR {
    void ft_assert(QString place, QString text);
}

#ifndef FT_IGNORE_ASSERTS
#define FT_ASSERT(expr, text)                                       \
    if (!(expr)) {                                                  \
        FT_ERROR::ft_assert(__FILE__ ":" TOSTRING(__LINE__), text); \
    }
#else
#define FT_ASSERT(expr, text)
#endif  // FT_IGNORE_ASSERTS

#endif  // INCLUDE_UTILS_H_
