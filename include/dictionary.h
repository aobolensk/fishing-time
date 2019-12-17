#ifndef INCLUDE_DICTIONARY_H_
#define INCLUDE_DICTIONARY_H_
#include <QMap>
#include <QVector>

class Game;

enum class Language {
    English,
    Russian
};

class Dictionary {
public:
    QMap <Language, QPair <QString, int>> languages;
    const QVector <QString> fishIds;
    const QVector <QString> itemIds;
    const QMap <QString, const QString*> itemNames;
    const QString fishingTime = "Fishing time";
    static constexpr int DICTIONARY_START = __LINE__;
        const QString
            about,
            aboutDescription,
            appearance,
            appearanceSettings,
            autoSavePeriod,
            autoSavePeriodSet,
            back,
            basicNet,
            bream,
            builtIn,
            buy,
            carp,
            changePassword,
            clear,
            click,
            clicksCount,
            coins,
            colorTheme,
            commandReturned,
            configFile,
            confirmPassword,
            confirmPasswordWarning,
            console,
            controls,
            credits,
            darkTheme,
            deleteAccount,
            deleteAccountConfirmation,
            demoMode,
            demoModeWarning,
            dialog,
            edit,
            empty,
            emptyLoginWarning,
            emptyPasswordWarning,
            enter,
            eraseAllData,
            eraseAllDataConfirmation,
            exit,
            exitConfirmation,
            experience,
            fish,
            fishLabelText,
            font,
            forbiddenSymbol,
            forgotPassword,
            goToPreviousMenu,
            hideUIElements,
            id,
            ide,
            incorrectPassword,
            information,
            invalidArgumentsFormat,
            invalidOldPasswordWarning,
            invalidValue,
            inventory,
            inventoryDescription,
            inventoryType,
            item,
            itemNotFound,
            items,
            itemStatistics,
            jumpToBottom,
            language,
            level,
            lightTheme,
            listOfAllCommands,
            location,
            locationDescription,
            log,
            logDebug,
            logError,
            logFile,
            logIn,
            logInfo,
            logOut,
            logWarning,
            loggerLevel,
            loggerLevelDebug,
            loggerLevelRelease,
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
            oldPassword,
            open,
            otherItems,
            password,
            passwordHasBeenReseted,
            passwordIsChanged,
            perch,
            permissionError,
            pike,
            popUp,
            price,
            privilegeLevelCommon,
            privilegeLevelSuper,
            profile,
            quantity,
            quantityShouldBeANumber,
            quantityShouldBeMoreThanZero,
            rating,
            reportAnError,
            resetPasswordConfirmation,
            roach,
            saving,
            savingIsComplete,
            selectItemFromList,
            sellerText,
            set,
            settings,
            setup,
            showBackgroundImages,
            signUp,
            signupMenuText,
            start,
            statistics,
            store,
            successfullyLoggedIn,
            successfullyLoggedOut,
            thisUserAlreadyExistsText,
            timePlayed,
            timeShouldBeANumber,
            toggleFullscreenMode,
            unknownCommand,
            unknownUser,
            useManToGetDescription,
            userProfileText,
            userSettings,
            userSettingsText,
            username,
            warning,
            youAreAlreadyLoggedIn,
            youAreNotLoggedIn,
            youDontHaveEnoughCoins,
            youDontHaveEnoughItems,
            yourPrivilegeLevel;
    struct Commands {
        const QString
            echo,
            login,
            signup,
            password,
            delete_account,
            click,
            gui,
            logout,
            save,
            about,
            version,
            aboutme,
            autosave,
            logging,
            language,
            location,
            privilege,
            market,
            su,
            clear,
            inventory,
            give,
            experience,
            rating,
            exit,
            time,
            help,
            man;
    } commands;
    QMap <QString, QString> stats = {
        {"stats.got", ""},
        {"stats.sold", ""},
        {"stats.bought", ""},
        {"stats.caught", ""},
        {"stats.undefined", ""}
    };
    QMap <QString, QString> locations = {
        {"locations.volga", ""},
        {"locations.oka", ""}
    };
    static constexpr int DICTIONARY_END = __LINE__;
private:
    int numberOfStrings = 0;
    Game *game;
public:
    Dictionary(Game *game);
    double getReadiness(Language l);
    int getNumberOfEntries(Language l);
    int getTotalNumberOfEntries();
    void setLanguage(Language l, bool initialSetup = false);
    const QString &getItemName(const QString &id) const;
};
#endif  // INCLUDE_DICTIONARY_H_
