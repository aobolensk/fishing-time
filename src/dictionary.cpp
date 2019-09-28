#include <stdexcept>
#include <QDebug>
#include "dictionary.h"

static int updatesCount = 0;

Dictionary::Dictionary() :
        languages({
            {Language::English, {"English", 0}},
            {Language::Russian, {"Russian", 0}}
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
    for (int i = languages.count() - 1; i >= 0; --i)
        this->setLanguage((Language)i);
    numberOfStrings = updatesCount;
    if (getReadiness(Language::English) != 100.)
        throw std::logic_error("Default language (English) does not contain all necessary translations. "
                                 "Fix it by adding all translations to Dictionary::setLanguage -> case Language::English");
}

const QString &Dictionary::getItemName(const QString &itemId) const {
    auto it = itemNames.find(itemId);
    if (it == itemNames.end())
        return invalidValue;
    return *(it.value());
}


double Dictionary::getReadiness(Language l) {
    return (double)languages[l].second / (DICTIONARY_END - DICTIONARY_START - 5) * 100.;
}

#define SET(string) (++updatesCount); (*(const_cast<QString*>(&string)))

void Dictionary::setLanguage(Language l) {
    updatesCount = 0;
    switch (l) {
    case Language::English: {
        SET(about) = "About";
        SET(aboutDescription) = "Fishing Time<br>"
                                "Official repo: <a href=\"%1\">%1</a><br>"
                                "Version: " COMMIT_HASH "<br>"
                                "Qt version: " QT_VERSION_STR "<br>";
        SET(autoSavePeriod) = "Autosave period";
        SET(back) = "Back";
        SET(basicNet) = "Basic net";
        SET(bream) = "Bream";
        SET(builtIn) = "Built-in";
        SET(buy) = "Buy";
        SET(carp) = "Carp";
        SET(changePassword) = "Change password";
        SET(click) = "Click";
        SET(clicksCount) = "Clicks count";
        SET(coins) = "Coins";
        SET(commandReturned) = "Command %1 returned %2";
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
        SET(eraseAllData) = "Erase all data";
        SET(eraseAllDataConfirmation) = "Do you really want to erase all your data?";
        SET(exit) = "Exit";
        SET(exitConfirmation) = "Do you want to exit?";
        SET(fishLabelText) = "Fish that can be caught in location %1:\n%2";
        SET(font) = "Font";
        SET(id) = "Id";
        SET(ide) = "Ide";
        SET(incorrectPassword) = "Incorrect password!";
        SET(information) = "Information";
        SET(invalidOldPasswordWarning) = "Incorrect old password";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Inventory";
        SET(inventoryDescription) = "Inventory of player %1";
        SET(inventoryType) = "Inventory type";
        SET(language) = "Language";
        SET(location) = "Location";
        SET(logError) = "[ERROR]";
        SET(logIn) = "Log in";
        SET(logInfo) = "[INFO]";
        SET(logOut) = "Log out";
        SET(logWarning) = "[WARNING]";
        SET(mainLabelText) = "Welcome, %1\nCoins: %2\nTotal clicks: %3\n";
        SET(mainMenuText) = "%1";
        SET(market) = "Market";
        SET(marketDescription) = "You can sell fish that you caught here. Just choose quantity and press button. All these deals update once a day.";
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
        SET(permissionError) = "You do not have permission to perform command %1";
        SET(pike) = "Pike";
        SET(popUp) = "Pop-up";
        SET(price) = "Price";
        SET(quantity) = "Quantity";
        SET(quantityShouldBeANumber) = "Quantity should be a number";
        SET(quantityShouldBeMoreThanZero) = "Quantity should be more than zero";
        SET(rating) = "Rating";
        SET(roach) = "Roach";
        SET(selectItemFromList) = "Select item from list";
        SET(sellerText) = "Seller %1\nbuys %2\nfor %3 coins each\n\nYou have: %4";
        SET(settings) = "Settings";
        SET(setup) = "Setup";
        SET(signUp) = "Sign up";
        SET(signupMenuText) = "Create new user.\nEnter your login and password to get registered.";
        SET(start) = "Start";
        SET(statistics) = "Statistics";
        SET(store) = "Store";
        SET(successfullyLoggedIn) = "Successfully logged in as \"%1\"";
        SET(thisUserAlreadyExistsText) = "This user already exists";
        SET(unknownCommand) = "Unknown command: %1";
        SET(unknownUser) = "User \"%1\" is not found";
        SET(userSettings) = "User settings";
        SET(userSettingsText) = "User: %1";
        SET(username) = "Username";
        SET(volga) = "Volga";
        SET(warning) = "Warning";
        SET(youDontHaveEnoughCoins) = "You don't have enough coins";
        SET(youDontHaveEnoughItems) = "You don't have enough items";

        SET(commands.echo) =
            "Print arguments<br>"
            "Usage: echo &lt;argument1&gt; &lt;argument2&gt; ...";
        SET(commands.login) =
            "Log in to account<br>"
            "Usage: login &lt;login&gt; &lt;password&gt;";
        SET(commands.signup) =
            "Go to sign up menu<br>"
            "Usage: signup";
        SET(commands.click) =
            "Perform click<br>"
            "Usage: click";
        SET(commands.logout) =
            "Log out and go to main menu<br>"
            "Usage: logout";
        SET(commands.save) =
            "Save<br>"
            "Usage: save";
        SET(commands.about) =
            "Print information about this game<br>"
            "Usage: about";
        SET(commands.aboutme) =
            "Print information about current user<br>"
            "Usage: aboutme";
        SET(commands.settings) =
            "Get information about the settings or edit the settings<br>"
            "Usage: settings get &lt;setting_name&gt;<br>"
            "List of supported settings:<br>"
            "\tautosave - auto save period<br>"
            "\tlanguage - current language";
        SET(commands.privilege) =
            "Print privilege level of current user<br>"
            "Usage: privilege";
        SET(commands.clear) =
            "Clear console output<br>"
            "Usage: clear";
        SET(commands.inventory) =
            "Show player's inventory<br>"
            "Usage: inventory";
        SET(commands.exit) =
            "Exit from the game<br>"
            "Usage: exit";
        SET(commands.help) =
            "Print list of all existing commands<br>"
            "Usage: help";
        SET(commands.man) =
            "Print manual for commands<br>"
            "Usage: man &lt;command1&gt; &lt;command2&gt; ...";

        languages[Language::English].second = updatesCount;
        break;
    } case Language::Russian: {
        SET(about) = "О программе";
        SET(aboutDescription) = "Fishing Time<br>"
                                "Официальный репозиторий: <a href=\"%1\">%1</a><br>"
                                "Версия: " COMMIT_HASH "<br>"
                                "Версия Qt: " QT_VERSION_STR "<br>";
        SET(autoSavePeriod) = "Период автосохранения";
        SET(back) = "Назад";
        SET(basicNet) = "Базовая сеть";
        SET(bream) = "Лещ";
        SET(builtIn) = "Встроенный";
        SET(buy) = "Купить";
        SET(carp) = "Карп";
        SET(changePassword) = "Сменить пароль";
        SET(click) = "Нажимай!";
        SET(clicksCount) = "Количество кликов";
        SET(coins) = "Монет";
        SET(commandReturned) = "Команда %1 завершилась с кодом %2";
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
        SET(eraseAllData) = "Удалить все данные";
        SET(eraseAllDataConfirmation) = "Вы действительно хотите удалить все данные?";
        SET(exit) = "Выход";
        SET(exitConfirmation) = "Вы действительно хотите выйти из игры?";
        SET(fishLabelText) = "Рыба, которую можно поймать в локации %1:\n%2";
        SET(font) = "Шрифт";
        SET(id) = "Идентификатор";
        SET(ide) = "Язь";
        SET(incorrectPassword) = "Неверный пароль!";
        SET(information) = "Информация";
        SET(invalidOldPasswordWarning) = "Неверно введен старый пароль";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Инвентарь";
        SET(inventoryDescription) = "Инвентарь игрока %1";
        SET(inventoryType) = "Тип инвентаря";
        SET(language) = "Язык";
        SET(location) = "Локация";
        SET(logError) = "[ОШИБКА]";
        SET(logIn) = "Войти";
        SET(logInfo) = "[ИНФО]";
        SET(logOut) = "Выйти";
        SET(logWarning) = "[ПРЕДУПРЕЖДЕНИЕ]";
        SET(mainLabelText) = "Добро пожаловать, %1\nМонет: %2\nВсего кликов: %3\n";
        SET(mainMenuText) = "%1";
        SET(market) = "Рынок";
        SET(marketDescription) = "Вы можете продать пойманную рыбу здесь. Просто выберите количество и нажмите на кнопку. Все эти сделки обновляются раз в день.";
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
        SET(permissionError) = "У вас недостаточно привилегий для выполнения команды %1";
        SET(pike) = "Щука";
        SET(popUp) = "Выпадающий";
        SET(price) = "Цена";
        SET(quantity) = "Количество";
        SET(quantityShouldBeANumber) = "Количество должно быть числом";
        SET(quantityShouldBeMoreThanZero) = "Количество должно быть больше нуля";
        SET(rating) = "Рейтинг";
        SET(roach) = "Плотва";
        SET(selectItemFromList) = "Выберите предмет из списка";
        SET(sellerText) = "Продавец %1\nпокупает %2\nза %3 монет каждый товар\n\nУ вас есть: %4";
        SET(settings) = "Настройки";
        SET(setup) = "Настроить";
        SET(signUp) = "Зарегистрироваться";
        SET(signupMenuText) = "Создание нового пользователя\nВведите логин и пароль, чтобы зарегистрироваться.";
        SET(start) = "Начать";
        SET(statistics) = "Статистика";
        SET(store) = "Магазин";
        SET(successfullyLoggedIn) = "Добро пожаловать, %1";
        SET(thisUserAlreadyExistsText) = "Пользователь с таким логином уже существует";
        SET(unknownCommand) = "Неизвестная команда: %1";
        SET(unknownUser) = "Пользователь \"%1\" не найден";
        SET(userSettings) = "Настройки пользователя";
        SET(userSettingsText) = "Пользователь: %1";
        SET(username) = "Логин";
        SET(volga) = "Волга";
        SET(warning) = "Внимание";
        SET(youDontHaveEnoughCoins) = "Недостаточно монет";
        SET(youDontHaveEnoughItems) = "Недостаточно предметов";

        SET(commands.echo) =
            "Вывести аргументы<br>"
            "Использование: echo &lt;аргумент1&gt; &lt;аргумент2&gt; ...";
        SET(commands.login) =
            "Войти в аккаунт<br>"
            "Использование: login &lt;логин&gt; &lt;пароль&gt;";
        SET(commands.signup) =
            "Перейти в меню регистрации<br>"
            "Использование: signup";
        SET(commands.click) =
            "Сделать клик<br>"
            "Использование: click";
        SET(commands.logout) =
            "Выйти из аккаунта и перейти в главное меню<br>"
            "Использование: logout";
        SET(commands.save) =
            "Сохранить<br>"
            "Использование: save";
        SET(commands.about) =
            "Вывести информацию об игре<br>"
            "Использование: about";
        SET(commands.aboutme) =
            "Вывести информацию о текущем пользователе<br>"
            "Использование: aboutme";
        SET(commands.settings) =
            "Получить информацию о настройках или отредактировать настройки<br>"
            "Использование: settings get &lt;setting_name&gt;<br>"
            "Список поддерживаемых настроек:<br>"
            "\tautosave - период автосохранения<br>"
            "\tlanguage - текущий язык";
        SET(commands.privilege) =
            "Вывести уровень привилегий текущего пользователя<br>"
            "Использование: privilege";
        SET(commands.clear) =
            "Очистить окно консоли<br>"
            "Использование: clear";
        SET(commands.inventory) =
            "Показать инвентарь игрока<br>"
            "Использование: inventory";
        SET(commands.exit) =
            "Выйти из игры<br>"
            "Использование: exit";
        SET(commands.help) =
            "Вывести список всех команд<br>"
            "Использование: help";
        SET(commands.man) =
            "Вывести мануал для команды<br>"
            "Использование: man &lt;команда1&gt; &lt;команда2&gt; ...";

        languages[Language::Russian].second = updatesCount;
        break;
    } default: {
        qDebug() << "Unknown language";
        break;
    }
    }
}
