#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
#include <QVector>
#include <QMap>

enum class Language {
    English
};

class Dictionary {
private:
    QMap <QString, const QString*> itemNames;
public:
    static constexpr int DICTIONARY_START = __LINE__;
    const QString
            back,
            carp,
            click,
            dialog,
            enterYourLoginHereText,
            exit,
            information,
            invalidLoginText,
            invalidValue,
            inventory,
            logIn,
            market,
            name,
            newUserCreatedText,
            perch,
            pike,
            quantity,
            signUp,
            start,
            thisUserAlreadyExistsText,
            volga,
            warning;
    static constexpr int DICTIONARY_END = __LINE__;
    Dictionary();
    void setLanguage(Language l);
    const QString &getItemName(const QString &id) const;
};
#endif  // INCLUDE_DICTIONARY_H_
