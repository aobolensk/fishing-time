#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
#include <QVector>
#include <QMap>

class Game;

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
            colorTheme,
            commandReturned,
            confirmPassword,
            confirmPasswordWarning,
            console,
            darkTheme,
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
            forbiddenSymbol,
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
            lightTheme,
            location,
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
            permissionError,
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
            successfullyLoggedIn,
            thisUserAlreadyExistsText,
            unknownCommand,
            unknownUser,
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
            aboutme,
            settings,
            privilege,
            clear,
            inventory,
            exit,
            time,
            help,
            man;
    } commands;
    static constexpr int DICTIONARY_END = __LINE__;
private:
    int numberOfStrings = 0;
    Game *game;
public:
    Dictionary(Game *game);
    double getReadiness(Language l);
    void setLanguage(Language l, bool initialSetup = false);
    const QString &getItemName(const QString &id) const;
};
#endif  // INCLUDE_DICTIONARY_H_
