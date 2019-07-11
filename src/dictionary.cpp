#include <stdexcept>
#include "dictionary.h"
#include "mainwindow.h"

Dictionary::Dictionary() :
        languages({
            "English",
            "Russian"
        }),
        itemIds({
            "fish.bream",
            "fish.carp",
            "fish.ide",
            "fish.perch",
            "fish.pike",
            "fish.roach"
        }),
        itemNames({
            {"fish.bream", &bream},
            {"fish.carp", &carp},
            {"fish.ide", &ide},
            {"fish.perch", &perch},
            {"fish.pike", &pike},
            {"fish.roach", &roach}
        }) {
}

const QString &Dictionary::getItemName(const QString &id) const {
    auto it = itemNames.find(id);
    if (it == itemNames.end())
        return invalidValue;
    return *(it.value());
}

#define SET(string) (*(const_cast<QString*>(&string)))

void Dictionary::setLanguage(Language l) {
    switch (l) {
    case Language::English: {
        constexpr int ENGLISH_START = __LINE__;
        SET(back) = "Back";
        SET(bream) = "Bream";
        SET(buy) = "Buy";
        SET(carp) = "Carp";
        SET(click) = "Click";
        SET(dialog) = "Dialog";
        SET(enterYourLoginHereText) = "Enter your login here";
        SET(exit) = "Exit";
        SET(ide) = "Ide";
        SET(information) = "Information";
        SET(invalidLoginText) = "Invalid login";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Inventory";
        SET(logIn) = "Log in";
        SET(mainLabelText) = "Welcome, %1\nCoins: %2\nTotal clicks: %3\n";
        SET(market) = "Market";
        SET(name) = "Name";
        SET(oka) = "Oka";
        SET(newUserCreatedText) = "New user \"%1\" successfully created";
        SET(quantity) = "Quantity";
        SET(quantityShouldBeANumber) = "Quantity should be a number";
        SET(quantityShouldBeMoreThanZero) = "Quantity should be more than zero";
        SET(roach) = "Roach";
        SET(perch) = "Perch";
        SET(pike) = "Pike";
        SET(sellerText) = "Seller %1\nbuys %2\nfor %3 coins each\n\nYou have: %4";
        SET(signUp) = "Sign up";
        SET(start) = "Start";
        SET(store) = "Store";
        SET(thisUserAlreadyExistsText) = "This user already exists";
        SET(volga) = "Volga";
        SET(warning) = "Warning";
        SET(youDontHaveEnoughItems) = "You don't have enough items";
        break;
        constexpr int ENGLISH_END = __LINE__;
        static_assert((DICTIONARY_END - DICTIONARY_START) == (ENGLISH_END - ENGLISH_START));
    } case Language::Russian: {
        constexpr int RUSSIAN_START = __LINE__;
        SET(back) = "Назад";
        SET(bream) = "Лещ";
        SET(buy) = "Купить";
        SET(carp) = "Карп";
        SET(click) = "Нажимай!";
        SET(dialog) = "Диалог";
        SET(enterYourLoginHereText) = "Введите ваш логин";
        SET(exit) = "Выход";
        SET(ide) = "Язь";
        SET(information) = "Информация";
        SET(invalidLoginText) = "Неверный логин";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Инвентарь";
        SET(logIn) = "Войти";
        SET(mainLabelText) = "Добро пожаловать, %1\nМонет: %2\nВсего кликов: %3\n";
        SET(market) = "Рынок";
        SET(name) = "Имя";
        SET(oka) = "Ока";
        SET(newUserCreatedText) = "Новый пользователь \"%1\" успешно создан";
        SET(quantity) = "Количество";
        SET(quantityShouldBeANumber) = "Количество должно быть числом";
        SET(quantityShouldBeMoreThanZero) = "Количество должно быть больше нуля";
        SET(roach) = "Плотва";
        SET(perch) = "Окунь";
        SET(pike) = "Щука";
        SET(sellerText) = "Продавец %1\nпокупает %2\nза %3 монет каждый товар\n\nУ вас есть: %4";
        SET(signUp) = "Зарегистрироваться";
        SET(start) = "Начать";
        SET(store) = "Магазин";
        SET(thisUserAlreadyExistsText) = "Пользователь с таким логином уже существует";
        SET(volga) = "Волга";
        SET(warning) = "Внимание";
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
