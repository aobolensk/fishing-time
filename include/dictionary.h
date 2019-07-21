#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
#include <QVector>
#include <QMap>

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
            autoSavePeriod,
            back,
            bream,
            buy,
            carp,
            click,
            dialog,
            enterYourLoginHereText,
            exit,
            exitConfirmation,
            fishLabelText,
            ide,
            information,
            invalidLoginText,
            invalidValue,
            inventory,
            language,
            logIn,
            mainLabelText,
            market,
            min,
            name,
            nets,
            newUserCreatedText,
            oka,
            perch,
            pike,
            quantity,
            quantityShouldBeANumber,
            quantityShouldBeMoreThanZero,
            roach,
            selectItemFromList,
            sellerText,
            settings,
            signUp,
            start,
            store,
            thisUserAlreadyExistsText,
            volga,
            warning,
            youDontHaveEnoughCoins,
            youDontHaveEnoughItems;
    static constexpr int DICTIONARY_END = __LINE__;
    Dictionary();
    void setLanguage(Language l);
    const QString &getItemName(const QString &id) const;
};
#endif  // INCLUDE_DICTIONARY_H_
