#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
#include <QVector>
#include <QMap>

enum class Language {
    English
};

class Dictionary {
public:
    const QVector <QString> itemIds;
    const QMap <QString, const QString*> itemNames;
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
            mainLabelText,
            market,
            name,
            newUserCreatedText,
            perch,
            pike,
            quantity,
            quantityShouldBeANumber,
            quantityShouldBeMoreThanZero,
            sellerText,
            signUp,
            start,
            thisUserAlreadyExistsText,
            volga,
            warning,
            youDontHaveEnoughItems;
    static constexpr int DICTIONARY_END = __LINE__;
    Dictionary();
    void setLanguage(Language l);
    const QString &getItemName(const QString &id) const;
};
#endif  // INCLUDE_DICTIONARY_H_
