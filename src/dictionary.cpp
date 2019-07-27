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
        SET(autoSavePeriod) = "Autosave period:";
        SET(back) = "Back";
        SET(basicNet) = "Basic net";
        SET(bream) = "Bream";
        SET(buy) = "Buy";
        SET(carp) = "Carp";
        SET(click) = "Click";
        SET(clicksCount) = "Clicks count";
        SET(console) = "Console";
        SET(demoMode) = "Demo mode";
        SET(demoModeWarning) = "You run the game in demo mode. Some functions may be not available.";
        SET(dialog) = "Dialog";
        SET(empty) = "<EMPTY>";
        SET(emptyLoginWarning) = "Login is empty!";
        SET(enterYourLoginHereText) = "Enter your login here";
        SET(exit) = "Exit";
        SET(exitConfirmation) = "Do you want to exit?";
        SET(fishLabelText) = "Fish that can be caught in location %1:\n%2";
        SET(id) = "Id";
        SET(ide) = "Ide";
        SET(incorrectPassword) = "Incorrect password!";
        SET(information) = "Information";
        SET(invalidLoginText) = "Invalid login";
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
        SET(nets) = "Nets";
        SET(netsDescription) = "In this menu you can put nets in order to catch fish in background.\nYou can buy nets in the store.\nYou can add one net to each cell.";
        SET(netSlot) = "Net slot %1\nNet: %2";
        SET(newUserCreatedText) = "New user \"%1\" successfully created";
        SET(oka) = "Oka";
        SET(perch) = "Perch";
        SET(pike) = "Pike";
        SET(price) = "Price";
        SET(quantity) = "Quantity";
        SET(quantityShouldBeANumber) = "Quantity should be a number";
        SET(quantityShouldBeMoreThanZero) = "Quantity should be more than zero";
        SET(roach) = "Roach";
        SET(selectItemFromList) = "Select item from list";
        SET(sellerText) = "Seller %1\nbuys %2\nfor %3 coins each\n\nYou have: %4";
        SET(settings) = "Settings";
        SET(signUp) = "Sign up";
        SET(signupMenuText) = "Create new user";
        SET(start) = "Start";
        SET(statistics) = "Statistics";
        SET(store) = "Store";
        SET(thisUserAlreadyExistsText) = "This user already exists";
        SET(volga) = "Volga";
        SET(userSettings) = "User settings";
        SET(warning) = "Warning";
        SET(youDontHaveEnoughCoins) = "You don't have enough coins";
        SET(youDontHaveEnoughItems) = "You don't have enough items";
        break;
        constexpr int ENGLISH_END = __LINE__;
        static_assert((DICTIONARY_END - DICTIONARY_START) == (ENGLISH_END - ENGLISH_START));
    } case Language::Russian: {
        constexpr int RUSSIAN_START = __LINE__;
        SET(autoSavePeriod) = "Период автосохранения:";
        SET(back) = "Назад";
        SET(basicNet) = "Базовая сеть";
        SET(bream) = "Лещ";
        SET(buy) = "Купить";
        SET(carp) = "Карп";
        SET(click) = "Нажимай!";
        SET(clicksCount) = "Количество кликов";
        SET(console) = "Консоль";
        SET(demoMode) = "Демо-режим";
        SET(demoModeWarning) = "Вы запускаете игру в демо-режиме. Некоторые функции могут быть недоступны.";
        SET(dialog) = "Диалог";
        SET(empty) = "<ПУСТО>";
        SET(emptyLoginWarning) = "Логин пуст!";
        SET(enterYourLoginHereText) = "Введите ваш логин";
        SET(exit) = "Выход";
        SET(exitConfirmation) = "Вы действительно хотите выйти из игры?";
        SET(fishLabelText) = "Рыба, которую можно поймать в локации %1:\n%2";
        SET(id) = "Идентификатор";
        SET(ide) = "Язь";
        SET(incorrectPassword) = "Неверный пароль!";
        SET(information) = "Информация";
        SET(invalidLoginText) = "Неверный логин";
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
        SET(nets) = "Сети";
        SET(netsDescription) = "В этом меню Вы можете поставить сети, чтобы ловить рыбу в пассивном режиме.\nВы можете приобрести сети в магазине.\nВы можете добавить одну сеть в каждую из ячеек.";
        SET(netSlot) = "Слот для сетей %1\nСеть: %2";
        SET(newUserCreatedText) = "Новый пользователь \"%1\" успешно создан";
        SET(oka) = "Ока";
        SET(perch) = "Окунь";
        SET(pike) = "Щука";
        SET(price) = "Цена";
        SET(quantity) = "Количество";
        SET(quantityShouldBeANumber) = "Количество должно быть числом";
        SET(quantityShouldBeMoreThanZero) = "Количество должно быть больше нуля";
        SET(roach) = "Плотва";
        SET(selectItemFromList) = "Выберите предмет из списка";
        SET(sellerText) = "Продавец %1\nпокупает %2\nза %3 монет каждый товар\n\nУ вас есть: %4";
        SET(settings) = "Настройки";
        SET(signUp) = "Зарегистрироваться";
        SET(signupMenuText) = "Создание нового пользователя";
        SET(start) = "Начать";
        SET(statistics) = "Статистика";
        SET(store) = "Магазин";
        SET(thisUserAlreadyExistsText) = "Пользователь с таким логином уже существует";
        SET(userSettings) = "Настройки пользователя";
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
