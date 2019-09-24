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
    QMap <Language, QPair <QString, int>> languages;
    const QVector <QString> itemIds;
    const QMap <QString, const QString*> itemNames;
    const QString fishingTime = "Fishing time";
    static constexpr int DICTIONARY_START = __LINE__;
        const QString
            about,
            aboutDescription,
            autoSavePeriod,
            back,
            basicNet,
            bream,
            builtIn,
            buy,
            carp,
            changePassword,
            click,
            clicksCount,
            coins,
            confirmPassword,
            confirmPasswordWarning,
            console,
            deleteAccount,
            deleteAccountConfirmation,
            demoMode,
            demoModeWarning,
            dialog,
            empty,
            emptyLoginWarning,
            emptyPasswordWarning,
            eraseAllData,
            eraseAllDataConfirmation,
            exit,
            exitConfirmation,
            fishLabelText,
            font,
            id,
            ide,
            incorrectPassword,
            information,
            invalidOldPasswordWarning,
            invalidValue,
            inventory,
            inventoryDescription,
            inventoryType,
            language,
            logError,
            logIn,
            logInfo,
            logOut,
            logWarning,
            mainLabelText,
            mainMenuText,
            market,
            marketDescription,
            min,
            name,
            netSlot,
            nets,
            netsDescription,
            newPassword,
            newPasswordConfirmation,
            newUserCreatedText,
            oka,
            oldPassword,
            password,
            passwordIsChanged,
            perch,
            pike,
            popUp,
            price,
            quantity,
            quantityShouldBeANumber,
            quantityShouldBeMoreThanZero,
            rating,
            roach,
            selectItemFromList,
            sellerText,
            settings,
            setup,
            signUp,
            signupMenuText,
            start,
            statistics,
            store,
            thisUserAlreadyExistsText,
            userSettings,
            userSettingsText,
            username,
            volga,
            warning,
            youDontHaveEnoughCoins,
            youDontHaveEnoughItems;
    struct Commands {
        const QString
            echo,
            login,
            signup,
            click,
            logout,
            save,
            about,
            settings,
            privilege,
            clear,
            exit,
            help,
            man;
    } commands;
    static constexpr int DICTIONARY_END = __LINE__;
private:
    int numberOfStrings = 0;
public:
    Dictionary();
    double getReadiness(Language l);
    void setLanguage(Language l);
    const QString &getItemName(const QString &id) const;
};
#endif  // INCLUDE_DICTIONARY_H_
