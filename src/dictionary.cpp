#include <stdexcept>
#include <QDebug>
#include "dictionary.h"

Dictionary::Dictionary() :
        languages({
            "English",
            "Russian"
        }),

        #define LIST_OF_ITEMS \
            X("fish.bream", &bream) \
            X("fish.carp", &carp) \
            X("fish.ide", &ide) \
            X("fish.perch", &perch) \
            X("fish.pike", &pike) \
            X("fish.roach", &roach) \
            X("net.basic", &basicNet) \

        #define X(itemId, itemNamePtr) \
              itemId ,
        itemIds({
            LIST_OF_ITEMS
            "item.undefined"
        }),
        #undef X

        #define X(itemId, itemNamePtr) \
            { itemId, itemNamePtr } ,
        itemNames({
            LIST_OF_ITEMS
            {"item.undefined", nullptr}
        })
        #undef X

        {

}

const QString &Dictionary::getItemName(const QString &itemId) const {
    auto it = itemNames.find(itemId);
    if (it == itemNames.end())
        return invalidValue;
    return *(it.value());
}

#define SET(string) (*(const_cast<QString*>(&string)))

void Dictionary::setLanguage(Language l) {
    switch (l) {
    case Language::English: {
        constexpr int ENGLISH_START = __LINE__;
        SET(autoSavePeriod) = "Autosave period";
        SET(back) = "Back";
        SET(basicNet) = "Basic net";
        SET(bream) = "Bream";
        SET(buy) = "Buy";
        SET(carp) = "Carp";
        SET(changePassword) = "Change password";
        SET(click) = "Click";
        SET(clicksCount) = "Clicks count";
        SET(coins) = "Coins";
        SET(confirmPassword) = "Confirm password";
        SET(confirmPasswordWarning) = "Password are not equal";
        SET(console) = "Console";
        SET(deleteAccount) = "Delete account";
        SET(deleteAccountConfirmation) = "Do you really want to delete your account?\nThis action can not be cancelled.";
        SET(demoMode) = "Demo mode";
        SET(demoModeWarning) = "You run the game in demo mode. Some functions may be not available.";
        SET(dialog) = "Dialog";
        SET(empty) = "<EMPTY>";
        SET(emptyLoginWarning) = "Login is empty!";
        SET(emptyPasswordWarning) = "Do you really want to leave your password empty?";
        SET(exit) = "Exit";
        SET(exitConfirmation) = "Do you want to exit?";
        SET(fishLabelText) = "Fish that can be caught in location %1:\n%2";
        SET(id) = "Id";
        SET(ide) = "Ide";
        SET(incorrectPassword) = "Incorrect password!";
        SET(information) = "Information";
        SET(invalidOldPasswordWarning) = "Incorrect old password";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Inventory";
        SET(language) = "Language";
        SET(logError) = "[ERROR]";
        SET(logIn) = "Log in";
        SET(logInfo) = "[INFO]";
        SET(logOut) = "Log out";
        SET(logWarning) = "[WARNING]";
        SET(mainLabelText) = "Welcome, %1\nCoins: %2\nTotal clicks: %3\n";
        SET(mainMenuText) = "%1";
        SET(market) = "Market";
        SET(min) = "min";
        SET(name) = "Name";
        SET(netSlot) = "Net slot %1\nNet: %2";
        SET(nets) = "Nets";
        SET(netsDescription) = "In this menu you can put nets in order to catch fish in background.\nYou can buy nets in the store.\nYou can add one net to each cell.";
        SET(newPassword) = "New password";
        SET(newPasswordConfirmation) = "Confirm new password";
        SET(newUserCreatedText) = "New user \"%1\" successfully created";
        SET(oka) = "Oka";
        SET(oldPassword) = "Old password";
        SET(password) = "Password";
        SET(passwordIsChanged) = "Password is successfully changed";
        SET(perch) = "Perch";
        SET(pike) = "Pike";
        SET(price) = "Price";
        SET(quantity) = "Quantity";
        SET(quantityShouldBeANumber) = "Quantity should be a number";
        SET(quantityShouldBeMoreThanZero) = "Quantity should be more than zero";
        SET(rating) = "Rating";
        SET(roach) = "Roach";
        SET(selectItemFromList) = "Select item from list";
        SET(sellerText) = "Seller %1\nbuys %2\nfor %3 coins each\n\nYou have: %4";
        SET(settings) = "Settings";
        SET(signUp) = "Sign up";
        SET(signupMenuText) = "Create new user.\nEnter your login and password to get registered.";
        SET(start) = "Start";
        SET(statistics) = "Statistics";
        SET(store) = "Store";
        SET(thisUserAlreadyExistsText) = "This user already exists";
        SET(userSettings) = "User settings";
        SET(userSettingsText) = "User: %1";
        SET(username) = "Username";
        SET(volga) = "Volga";
        SET(warning) = "Warning";
        SET(youDontHaveEnoughCoins) = "You don't have enough coins";
        SET(youDontHaveEnoughItems) = "You don't have enough items";
        break;
        constexpr int ENGLISH_END = __LINE__;
        static_assert((DICTIONARY_END - DICTIONARY_START) == (ENGLISH_END - ENGLISH_START));
    } case Language::Russian: {
        constexpr int RUSSIAN_START = __LINE__;
        SET(autoSavePeriod) = "Период автосохранения";
        SET(back) = "Назад";
        SET(basicNet) = "Базовая сеть";
        SET(bream) = "Лещ";
        SET(buy) = "Купить";
        SET(carp) = "Карп";
        SET(changePassword) = "Сменить пароль";
        SET(click) = "Нажимай!";
        SET(clicksCount) = "Количество кликов";
        SET(coins) = "Монет";
        SET(confirmPassword) = "Подтвердите пароль";
        SET(confirmPasswordWarning) = "Пароли не совпадают";
        SET(console) = "Консоль";
        SET(deleteAccount) = "Удалить аккаунт";
        SET(deleteAccountConfirmation) = "Вы действительно хотите удалить аккаунт?\nЭто действие необратимо.";
        SET(demoMode) = "Демо-режим";
        SET(demoModeWarning) = "Вы запускаете игру в демо-режиме. Некоторые функции могут быть недоступны.";
        SET(dialog) = "Диалог";
        SET(empty) = "<ПУСТО>";
        SET(emptyLoginWarning) = "Логин пуст!";
        SET(emptyPasswordWarning) = "Вы действительно хотите оставить пароль пустым?";
        SET(exit) = "Выход";
        SET(exitConfirmation) = "Вы действительно хотите выйти из игры?";
        SET(fishLabelText) = "Рыба, которую можно поймать в локации %1:\n%2";
        SET(id) = "Идентификатор";
        SET(ide) = "Язь";
        SET(incorrectPassword) = "Неверный пароль!";
        SET(information) = "Информация";
        SET(invalidOldPasswordWarning) = "Неверно введен старый пароль";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Инвентарь";
        SET(language) = "Язык";
        SET(logError) = "[ОШИБКА]";
        SET(logIn) = "Войти";
        SET(logInfo) = "[ИНФО]";
        SET(logOut) = "Выйти";
        SET(logWarning) = "[ПРЕДУПРЕЖДЕНИЕ]";
        SET(mainLabelText) = "Добро пожаловать, %1\nМонет: %2\nВсего кликов: %3\n";
        SET(mainMenuText) = "%1";
        SET(market) = "Рынок";
        SET(min) = "мин";
        SET(name) = "Имя";
        SET(netSlot) = "Слот для сетей %1\nСеть: %2";
        SET(nets) = "Сети";
        SET(netsDescription) = "В этом меню Вы можете поставить сети, чтобы ловить рыбу в пассивном режиме.\nВы можете приобрести сети в магазине.\nВы можете добавить одну сеть в каждую из ячеек.";
        SET(newPassword) = "Новый пароль";
        SET(newPasswordConfirmation) = "Подтверждение нового пароля";
        SET(newUserCreatedText) = "Новый пользователь \"%1\" успешно создан";
        SET(oka) = "Ока";
        SET(oldPassword) = "Старый пароль";
        SET(password) = "Пароль";
        SET(passwordIsChanged) = "Пароль успешно изменен";
        SET(perch) = "Окунь";
        SET(pike) = "Щука";
        SET(price) = "Цена";
        SET(quantity) = "Количество";
        SET(quantityShouldBeANumber) = "Количество должно быть числом";
        SET(quantityShouldBeMoreThanZero) = "Количество должно быть больше нуля";
        SET(rating) = "Рейтинг";
        SET(roach) = "Плотва";
        SET(selectItemFromList) = "Выберите предмет из списка";
        SET(sellerText) = "Продавец %1\nпокупает %2\nза %3 монет каждый товар\n\nУ вас есть: %4";
        SET(settings) = "Настройки";
        SET(signUp) = "Зарегистрироваться";
        SET(signupMenuText) = "Создание нового пользователя\nВведите логин и пароль, чтобы зарегистрироваться.";
        SET(start) = "Начать";
        SET(statistics) = "Статистика";
        SET(store) = "Магазин";
        SET(thisUserAlreadyExistsText) = "Пользователь с таким логином уже существует";
        SET(userSettings) = "Настройки пользователя";
        SET(userSettingsText) = "Пользователь: %1";
        SET(username) = "Логин";
        SET(volga) = "Волга";
        SET(warning) = "Внимание";
        SET(youDontHaveEnoughCoins) = "Недостаточно монет";
        SET(youDontHaveEnoughItems) = "Недостаточно предметов";
        break;
        constexpr int RUSSIAN_END = __LINE__;
        static_assert((DICTIONARY_END - DICTIONARY_START) == (RUSSIAN_END - RUSSIAN_START));
    } default: {
        qDebug() << "Unknown language";
        break;
    }
    }
}
