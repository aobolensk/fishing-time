#include "dictionary.h"

Dictionary::Dictionary() {
    setLanguage(Language::English);
}

#define SET(string) (*(const_cast<QString*>(&string)))

void Dictionary::setLanguage(Language l) {
    switch (l) {
    case Language::English:
        constexpr int ENGLISH_START = __LINE__;
        SET(back) = "Back";
        SET(click) = "Click";
        SET(dialog) = "Dialog";
        SET(enterYourLoginHereText) = "Enter you login here";
        SET(exit) = "Exit";
        SET(information) = "Information";
        SET(invalidLoginText) = "Invalid login";
        SET(inventory) = "Inventory";
        SET(logIn) = "Log in";
        SET(market) = "Market";
        SET(name) = "Name";
        SET(newUserCreatedText) = "New user successfully created";
        SET(quantity) = "Quantity";
        SET(signUp) = "Sign up";
        SET(start) = "Start";
        SET(thisUserAlreadyExistsText) = "This user already exists";
        SET(warning) = "Warning";
        break;
        constexpr int ENGLISH_END = __LINE__;
        static_assert((DICTIONARY_END - DICTIONARY_START) == (ENGLISH_END - ENGLISH_START));
    }
}
