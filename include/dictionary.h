#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
#include <QVector>
#include <QMap>

class MainWindow;

enum class Language {
    English,
    Russian
};

class Dictionary {
public:
    const QVector <QString> languages;
    const QVector <QString> itemIds;
    const QMap <QString, const QString*> itemNames;
    static constexpr int DICTIONARY_START = __LINE__;
    const QString
            back,
            bream,
            carp,
            click,
            dialog,
            enterYourLoginHereText,
            exit,
            ide,
            information,
            invalidLoginText,
            invalidValue,
            inventory,
            logIn,
            mainLabelText,
            market,
            name,
            newUserCreatedText,
            oka,
            perch,
            pike,
            quantity,
            quantityShouldBeANumber,
            quantityShouldBeMoreThanZero,
            roach,
            sellerText,
            signUp,
            start,
            store,
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
