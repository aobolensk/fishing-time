#include "dictionary.h"

Dictionary::Dictionary() :
    itemIds({
        "fish.carp",
        "fish.perch",
        "fish.pike"
    }),
    itemNames({
        {"fish.carp", &carp},
        {"fish.perch", &perch},
        {"fish.pike", &pike}
    })
    {
    setLanguage(Language::English);
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
        SET(carp) = "Carp";
        SET(click) = "Click";
        SET(dialog) = "Dialog";
        SET(enterYourLoginHereText) = "Enter your login here";
        SET(exit) = "Exit";
        SET(information) = "Information";
        SET(invalidLoginText) = "Invalid login";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Inventory";
        SET(logIn) = "Log in";
        SET(mainLabelText) = "Welcome, %1\nClicks: %2\n";
        SET(market) = "Market";
        SET(name) = "Name";
        SET(newUserCreatedText) = "New user \"%1\" successfully created";
        SET(quantity) = "Quantity";
        SET(perch) = "Perch";
        SET(pike) = "Pike";
        SET(sellerText) = "Seller %1\nbuys %2\nfor %3 coins each";
        SET(signUp) = "Sign up";
        SET(start) = "Start";
        SET(thisUserAlreadyExistsText) = "This user already exists";
        SET(volga) = "Volga";
        SET(warning) = "Warning";
        break;
        constexpr int ENGLISH_END = __LINE__;
        static_assert((DICTIONARY_END - DICTIONARY_START) == (ENGLISH_END - ENGLISH_START));
    }
}
