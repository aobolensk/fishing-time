#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
#include <QVector>

enum class Language {
    English
};

struct Dictionary {
    static constexpr int DICTIONARY_START = __LINE__;
    const QString
            back,
            click,
            enterYourLoginHereText,
            exit,
            information,
            invalidLoginText,
            inventory,
            logIn,
            newUserCreatedText,
            quantity,
            signUp,
            start,
            thisUserAlreadyExistsText,
            warning;
    static constexpr int DICTIONARY_END = __LINE__;
    Dictionary();
    void setLanguage(Language l);
};
#endif  // INCLUDE_DICTIONARY_H_
