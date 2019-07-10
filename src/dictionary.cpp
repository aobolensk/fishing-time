#include "dictionary.h"
#include "mainwindow.h"

Dictionary::Dictionary(MainWindow *w) :
        window(w),
        itemIds({
            "fish.carp",
            "fish.perch",
            "fish.pike"
        }),
        itemNames({
            {"fish.carp", &carp},
            {"fish.perch", &perch},
            {"fish.pike", &pike}
        }) {
    setLanguage(window->cfg.language);
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
    case Language::English:
        constexpr int ENGLISH_START = __LINE__;
        SET(back) = "Back";
        SET(bream) = "Bream";
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
        SET(thisUserAlreadyExistsText) = "This user already exists";
        SET(volga) = "Volga";
        SET(warning) = "Warning";
        SET(youDontHaveEnoughItems) = "You don't have enough items";
        break;
        constexpr int ENGLISH_END = __LINE__;
        static_assert((DICTIONARY_END - DICTIONARY_START) == (ENGLISH_END - ENGLISH_START));
    }
}
