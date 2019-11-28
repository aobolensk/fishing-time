#include "dictionary.h"
#include "game.h"

static int updatesCount = 0;

Dictionary::Dictionary(Game *game) :
        languages({
            {Language::English, {"English", 0}},
            {Language::Russian, {"Russian", 0}}
        }),

        #define LIST_OF_FISH \
            X("fish.bream", &bream) \
            X("fish.carp", &carp) \
            X("fish.ide", &ide) \
            X("fish.perch", &perch) \
            X("fish.pike", &pike) \
            X("fish.roach", &roach) \

        #define LIST_OF_NETS \
            X("net.basic", &basicNet) \

        #define X(itemId, itemNamePtr) \
              itemId ,
        fishIds({
            LIST_OF_FISH
            "item.undefined"
        }),

        itemIds({
            LIST_OF_FISH
            LIST_OF_NETS
            "item.undefined"
        }),
        #undef X

        #define X(itemId, itemNamePtr) \
            { itemId, itemNamePtr } ,
        itemNames({
            LIST_OF_FISH
            LIST_OF_NETS
            {"item.undefined", nullptr}
        })
        #undef X
        ,
        game(game)

        {
    for (int i = languages.count() - 1; i >= 0; --i)
        this->setLanguage((Language)i, true);
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
    return (double)getNumberOfEntries(l) / getTotalNumberOfEntries() * 100.;
}

int Dictionary::getNumberOfEntries(Language l) {
    return languages[l].second;
}

int Dictionary::getTotalNumberOfEntries() {
    return (DICTIONARY_END - DICTIONARY_START - 10);
}

#define SET(string) (++updatesCount); (*(const_cast<QString*>(&string)))

void Dictionary::setLanguage(Language l, bool initialSetup) {
    updatesCount = 0;
    switch (l) {
    case Language::English: {
        SET(about) = "About";
        SET(aboutDescription) = "Fishing Time<br>"
                                "Official repo: <a href=\"%1\">%1</a><br>"
                                "Version: " COMMIT_HASH "<br>"
                                "Qt version: " QT_VERSION_STR "<br>"
                                "OS: %2<br>"
                                "Compiler: %3<br>";
        SET(autoSavePeriod) = "Autosave period";
        SET(autoSavePeriodSet) = "Autosave period is set to %1 minutes";
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
        SET(colorTheme) = "Color theme";
        SET(commandReturned) = "Command %1 returned %2";
        SET(configFile) = "Configuration file";
        SET(confirmPassword) = "Confirm password";
        SET(confirmPasswordWarning) = "Password are not equal";
        SET(console) = "Console";
        SET(darkTheme) = "Dark theme";
        SET(deleteAccount) = "Delete account";
        SET(deleteAccountConfirmation) = "Do you really want to delete your account?\nThis action can not be cancelled.";
        SET(demoMode) = "Demo mode";
        SET(demoModeWarning) = "You run the game in demo mode. Some functions may be not available.";
        SET(dialog) = "Dialog";
        SET(empty) = "<EMPTY>";
        SET(emptyLoginWarning) = "Login is empty!";
        SET(emptyPasswordWarning) = "Do you really want to leave your password empty?";
        SET(enter) = "Enter";
        SET(eraseAllData) = "Erase all data";
        SET(eraseAllDataConfirmation) = "Do you really want to erase all your data?";
        SET(exit) = "Exit";
        SET(exitConfirmation) = "Do you want to exit?";
        SET(experience) = "Experience";
        SET(fish) = "Fish";
        SET(fishLabelText) = "Fish that can be caught in location %1:\n%2";
        SET(font) = "Font";
        SET(forbiddenSymbol) = "Forbidden symbol: %1";
        SET(forgotPassword) = "Forgot password";
        SET(id) = "Id";
        SET(ide) = "Ide";
        SET(incorrectPassword) = "Incorrect password!";
        SET(information) = "Information";
        SET(invalidArgumentsFormat) = "Invalid arguments format for command %1. Check out 'man %1'";
        SET(invalidOldPasswordWarning) = "Incorrect old password";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Inventory";
        SET(inventoryDescription) = "Inventory of player %1";
        SET(inventoryType) = "Inventory type";
        SET(item) = "Item";
        SET(itemNotFound) = "Item %1 is not found";
        SET(items) = "Items";
        SET(itemStatistics) = "Item statistics";
        SET(jumpToBottom) = "Jump to bottom";
        SET(language) = "Language";
        SET(level) = "Level";
        SET(lightTheme) = "Light theme";
        SET(listOfAllCommands) = "List of all commands";
        SET(location) = "Location";
        SET(locationDescription) = "You can travel between locations to get different fish.\nChoose location:";
        SET(log) = "Log";
        SET(logDebug) = "[DEBUG]";
        SET(logError) = "[ERROR]";
        SET(logFile) = "Log file";
        SET(logIn) = "Log in";
        SET(logInfo) = "[INFO]";
        SET(logOut) = "Log out";
        SET(logWarning) = "[WARNING]";
        SET(loggerLevel) = "Logging level";
        SET(loggerLevelDebug) = "Debug (more logs)";
        SET(loggerLevelRelease) = "Release (less logs)";
        SET(mainLabelText) =
            "Welcome, %1\n"
            "Level: %2 (%3 / %4 XP)\n"
            "Coins: %5\n"
            "Total clicks: %6\n";
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
        SET(oldPassword) = "Old password";
        SET(open) = "Open";
        SET(otherItems) = "Other items";
        SET(password) = "Password";
        SET(passwordHasBeenReseted) = "Your password has been reseted. You can login with empty password and set your new password in user settings";
        SET(passwordIsChanged) = "Password is successfully changed";
        SET(perch) = "Perch";
        SET(permissionError) = "You do not have permission to perform command %1";
        SET(pike) = "Pike";
        SET(popUp) = "Pop-up";
        SET(price) = "Price";
        SET(privilegeLevelCommon) = "Common";
        SET(privilegeLevelSuper) = "Super";
        SET(profile) = "Profile";
        SET(quantity) = "Quantity";
        SET(quantityShouldBeANumber) = "Quantity should be a number";
        SET(quantityShouldBeMoreThanZero) = "Quantity should be more than zero";
        SET(rating) = "Rating";
        SET(resetPasswordConfirmation) = "Do you really want to reset your password?";
        SET(roach) = "Roach";
        SET(saving) = "Saving...";
        SET(savingIsComplete) = "Saving is complete";
        SET(selectItemFromList) = "Select item from list";
        SET(sellerText) = "Seller %1\nbuys %2\nfor %3 coins each\n\nYou have: %4";
        SET(settings) = "Settings";
        SET(setup) = "Setup";
        SET(showBackgroundImages) = "Show background images";
        SET(signUp) = "Sign up";
        SET(signupMenuText) = "Create new user.\nEnter your login and password to get registered.";
        SET(start) = "Start";
        SET(statistics) = "Statistics";
        SET(store) = "Store";
        SET(reportAnError) = "Report an error";
        SET(successfullyLoggedIn) = "Successfully logged in as \"%1\"";
        SET(successfullyLoggedOut) = "Successfully logged out";
        SET(thisUserAlreadyExistsText) = "This user already exists";
        SET(timePlayed) = "Time played";
        SET(timeShouldBeANumber) = "Time should be a number";
        SET(unknownCommand) = "Unknown command: %1";
        SET(unknownUser) = "User \"%1\" is not found";
        SET(useManToGetDescription) = "Use 'man &lt;command&gt;' to get description";
        SET(userProfileText) =
            "Name: %1\n"
            "Level: %2 (%3 / %4 XP)\n"
            "Coins: %5\n";
        SET(userSettings) = "User settings";
        SET(userSettingsText) = "User: %1";
        SET(username) = "Username";
        SET(warning) = "Warning";
        SET(youAreAlreadyLoggedIn) = "You are already logged in";
        SET(youAreNotLoggedIn) = "You are not logged in";
        SET(youDontHaveEnoughCoins) = "You don't have enough coins";
        SET(youDontHaveEnoughItems) = "You don't have enough items";
        SET(yourPrivilegeLevel) = "Your privilege level";

        SET(commands.echo) =
            "Print arguments<br>"
            "Usage: echo &lt;argument1&gt; &lt;argument2&gt; ...";
        SET(commands.login) =
            "Log in to account<br>"
            "Usage: login &lt;login&gt; &lt;password&gt;";
        SET(commands.signup) =
            "Sign up new user<br>"
            "Usage: signup &lt;login&gt; &lt;password&gt; &lt;password confirmation&gt; ";
        SET(commands.password) =
            "Manage password settings<br>"
            "Usage: password &lt;option&gt; &lt;option_args&gt;<br>"
            "List of supported options:<br>"
            "\tchange - change password<br>"
            "\t(password change &lt;old password&gt; &lt;new password&gt;"
            "&lt;new password confirmation&gt;)";
        SET(commands.delete_account) =
            "Delete an account (permanently!)<br>"
            "Usage: delete_account &lt;password&gt; &lt;password confirmation&gt;";
        SET(commands.click) =
            "Perform click<br>"
            "Usage: click";
        SET(commands.gui) =
            "Show GUI (graphical user interface) of the game<br>"
            "Usage: gui";
        SET(commands.logout) =
            "Log out and go to main menu<br>"
            "Usage: logout";
        SET(commands.save) =
            "Save<br>"
            "Usage: save";
        SET(commands.about) =
            "Print information about this game<br>"
            "Usage: about";
        SET(commands.version) =
            "Print verison of the game<br>"
            "Usage: version";
        SET(commands.aboutme) =
            "Print information about current user<br>"
            "Usage: aboutme";
        SET(commands.autosave) =
            "Set and get game autosave period<br>"
            "Usage:<br>"
            "\tautosave - get autosave period<br>"
            "\tautosave 60 - set autosave period to 60 minutes";
        SET(commands.logging) =
            "Set and get game logging level<br>"
            "Usage:<br>"
            "\tlogging - get logging level<br>"
            "\tlogging debug - set logging level to DEBUG<br>"
            "\tlogging release - set logging level to RELEASE";
        SET(commands.language) =
            "Set and get game language<br>"
            "Usage:<br>"
            "\tlanguage - get language<br>"
            "\tlanguage en - set language to ENGLISH<br>"
            "\tlanguage ru - set language to RUSSIAN";
        SET(commands.location) =
            "Go to locations<br>"
            "Usage:<br>"
            "\tlocation - get current location<br>"
            "\tlocation &lt;location name&gt; - go to specific location";
        SET(commands.privilege) =
            "Print privilege level of current user<br>"
            "Usage: privilege";
        SET(commands.market) =
            "Use market<br>"
            "Usage:<br>"
            "\tmarket - get all deals on the market";
        SET(commands.su) =
            "Toggle privilege level (common, super)<br>"
            "Usage: su";
        SET(commands.clear) =
            "Clear console output<br>"
            "Usage: clear";
        SET(commands.inventory) =
            "Show player's inventory<br>"
            "Usage: inventory";
        SET(commands.give) =
            "Give user some item<br>"
            "Usage: give &lt;item ID&gt; &lt;quantity&gt;<br>"
            "Only for superusers!";
        SET(commands.experience) =
            "Change user experience<br>"
            "Usage: experience &lt;amount&gt;<br>"
            "Only for superusers!";
        SET(commands.rating) =
            "Show users rating<br>"
            "Usage: rating";
        SET(commands.exit) =
            "Exit from the game<br>"
            "Usage: exit";
        SET(commands.time) =
            "Get current time<br>"
            "Usage: time";
        SET(commands.help) =
            "Print list of all existing commands<br>"
            "Usage: help";
        SET(commands.man) =
            "Print manual for commands<br>"
            "Usage: man &lt;command1&gt; &lt;command2&gt; ...";

        SET(stats["stats.got"]) = "Got";
        SET(stats["stats.sold"]) = "Sold";
        SET(stats["stats.bought"]) = "Bought";
        SET(stats["stats.caught"]) = "Caught";

        SET(locations["location.volga"]) = "Volga";
        SET(locations["location.oka"]) = "Oka";

        languages[Language::English].second = updatesCount;
        break;
    } case Language::Russian: {
        SET(about) = "О программе";
        SET(aboutDescription) = "Fishing Time<br>"
                                "Официальный репозиторий: <a href=\"%1\">%1</a><br>"
                                "Версия: " COMMIT_HASH "<br>"
                                "Версия Qt: " QT_VERSION_STR "<br>"
                                "ОС: %2<br>"
                                "Компилятор: %3<br>";
        SET(autoSavePeriod) = "Период автосохранения";
        SET(autoSavePeriodSet) = "Период автосохранения установлен в %1 минут";
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
        SET(colorTheme) = "Цветовая тема";
        SET(commandReturned) = "Команда %1 завершилась с кодом %2";
        SET(configFile) = "Файл конфигурации";
        SET(confirmPassword) = "Подтвердите пароль";
        SET(confirmPasswordWarning) = "Пароли не совпадают";
        SET(console) = "Консоль";
        SET(darkTheme) = "Темная тема";
        SET(deleteAccount) = "Удалить аккаунт";
        SET(deleteAccountConfirmation) = "Вы действительно хотите удалить аккаунт?\nЭто действие необратимо.";
        SET(demoMode) = "Демо-режим";
        SET(demoModeWarning) = "Вы запускаете игру в демо-режиме. Некоторые функции могут быть недоступны.";
        SET(dialog) = "Диалог";
        SET(empty) = "<ПУСТО>";
        SET(emptyLoginWarning) = "Логин пуст!";
        SET(emptyPasswordWarning) = "Вы действительно хотите оставить пароль пустым?";
        SET(enter) = "Ввод";
        SET(eraseAllData) = "Удалить все данные";
        SET(eraseAllDataConfirmation) = "Вы действительно хотите удалить все данные?";
        SET(exit) = "Выход";
        SET(exitConfirmation) = "Вы действительно хотите выйти из игры?";
        SET(experience) = "Опыт";
        SET(fish) = "Рыба";
        SET(fishLabelText) = "Рыба, которую можно поймать в локации %1:\n%2";
        SET(font) = "Шрифт";
        SET(forbiddenSymbol) = "Недопустимый символ: %1";
        SET(forgotPassword) = "Забыли пароль";
        SET(id) = "Идентификатор";
        SET(ide) = "Язь";
        SET(incorrectPassword) = "Неверный пароль!";
        SET(information) = "Информация";
        SET(invalidArgumentsFormat) = "Неверные аргументы для команды %1. Помощь: 'man %1'";
        SET(invalidOldPasswordWarning) = "Неверно введен старый пароль";
        SET(invalidValue) = "<INVALID>";
        SET(inventory) = "Инвентарь";
        SET(inventoryDescription) = "Инвентарь игрока %1";
        SET(inventoryType) = "Тип инвентаря";
        SET(item) = "Предмет";
        SET(itemNotFound) = "Предмет %1 не найден";
        SET(items) = "Предметы";
        SET(itemStatistics) = "Статистика предметов";
        SET(jumpToBottom) = "Перейти вниз";
        SET(language) = "Язык";
        SET(level) = "Уровень";
        SET(lightTheme) = "Светлая тема";
        SET(listOfAllCommands) = "Список всех команд";
        SET(location) = "Локация";
        SET(locationDescription) = "Вы можете перемещаться между локациями, чтобы получать разную рыбу.\nВыберите локацию:";
        SET(log) = "Лог";
        SET(logDebug) = "[ОТЛАДКА]";
        SET(logError) = "[ОШИБКА]";
        SET(logFile) = "Файл логов";
        SET(logIn) = "Войти";
        SET(logInfo) = "[ИНФО]";
        SET(logOut) = "Выйти";
        SET(logWarning) = "[ПРЕДУПРЕЖДЕНИЕ]";
        SET(loggerLevel) = "Уровень логов";
        SET(loggerLevelDebug) = "Отладка (больше логов)";
        SET(loggerLevelRelease) = "Выпуск (меньше логов)";
        SET(mainLabelText) =
            "Добро пожаловать, %1\n"
            "Уровень: %2 (%3 / %4 XP)\n"
            "Монет: %5\n"
            "Всего кликов: %6\n";
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
        SET(oldPassword) = "Старый пароль";
        SET(open) = "Открыть";
        SET(otherItems) = "Другие предметы";
        SET(password) = "Пароль";
        SET(passwordHasBeenReseted) = "Ваш пароль был сброшен. Теперь вы можете войти в игру с пустым паролем и установить новый пароль в настройках пользователя";
        SET(passwordIsChanged) = "Пароль успешно изменен";
        SET(perch) = "Окунь";
        SET(permissionError) = "У вас недостаточно привилегий для выполнения команды %1";
        SET(pike) = "Щука";
        SET(popUp) = "Выпадающий";
        SET(price) = "Цена";
        SET(privilegeLevelCommon) = "Общий";
        SET(privilegeLevelSuper) = "Супер";
        SET(profile) = "Профиль";
        SET(quantity) = "Количество";
        SET(quantityShouldBeANumber) = "Количество должно быть числом";
        SET(quantityShouldBeMoreThanZero) = "Количество должно быть больше нуля";
        SET(rating) = "Рейтинг";
        SET(reportAnError) = "Сообщить об ошибке";
        SET(resetPasswordConfirmation) = "Вы действительно хотите сбросить пароль?";
        SET(roach) = "Плотва";
        SET(saving) = "Сохранение...";
        SET(savingIsComplete) = "Сохранение завершено";
        SET(selectItemFromList) = "Выберите предмет из списка";
        SET(sellerText) = "Продавец %1\nпокупает %2\nза %3 монет каждый товар\n\nУ вас есть: %4";
        SET(settings) = "Настройки";
        SET(setup) = "Настроить";
        SET(showBackgroundImages) = "Показывать фоновые изображения";
        SET(signUp) = "Зарегистрироваться";
        SET(signupMenuText) = "Создание нового пользователя\nВведите логин и пароль, чтобы зарегистрироваться.";
        SET(start) = "Начать";
        SET(statistics) = "Статистика";
        SET(store) = "Магазин";
        SET(successfullyLoggedIn) = "Добро пожаловать, %1";
        SET(successfullyLoggedOut) = "Вы успешно вышли из аккаунта";
        SET(thisUserAlreadyExistsText) = "Пользователь с таким логином уже существует";
        SET(timePlayed) = "Проведено времени в игре";
        SET(timeShouldBeANumber) = "Время должно быть числом";
        SET(unknownCommand) = "Неизвестная команда: %1";
        SET(unknownUser) = "Пользователь \"%1\" не найден";
        SET(useManToGetDescription) = "Используйте 'man &lt;команда&gt;' чтобы получить описание";
        SET(userProfileText) =
            "Имя: %1\n"
            "Уровень: %2 (%3 / %4 XP)\n"
            "Количество монет: %5\n";
        SET(userSettings) = "Настройки пользователя";
        SET(userSettingsText) = "Пользователь: %1";
        SET(username) = "Логин";
        SET(warning) = "Внимание";
        SET(youAreAlreadyLoggedIn) = "Вы уже вошли в систему";
        SET(youAreNotLoggedIn) = "Вы не вошли в систему";
        SET(youDontHaveEnoughCoins) = "Недостаточно монет";
        SET(youDontHaveEnoughItems) = "Недостаточно предметов";
        SET(yourPrivilegeLevel) = "Ваш уровень привилегий";

        SET(commands.echo) =
            "Вывести аргументы<br>"
            "Использование: echo &lt;аргумент1&gt; &lt;аргумент2&gt; ...";
        SET(commands.login) =
            "Войти в аккаунт<br>"
            "Использование: login &lt;логин&gt; &lt;пароль&gt;";
        SET(commands.signup) =
            "Зарегистрировать нового пользователя<br>"
            "Использование: signup &lt;логин&gt; &lt;пароль&gt; &lt;подтверждение пароля&gt;";
        SET(commands.password) =
            "Управление настройками пароля<br>"
            "Использование: password &lt;операция&gt; &lt;аргументы_для_операции&gt;<br>"
            "Список поддерживаемых операций:<br>"
            "\tchange - изменить пароль<br>"
            "\t(password change &lt;старый пароль&gt; &lt;новый пароль&gt; "
            "&lt;подтверждение нового пароля&gt;)";
        SET(commands.delete_account) =
            "Удалить аккаунт (безвозвратно!)<br>"
            "Использование: delete_account &lt;пароль&gt; &lt;подтверждение пароля&gt;";
        SET(commands.click) =
            "Сделать клик<br>"
            "Использование: click";
        SET(commands.gui) =
            "Показать графический интерфейс игры<br>"
            "Использование: gui";
        SET(commands.logout) =
            "Выйти из аккаунта и перейти в главное меню<br>"
            "Использование: logout";
        SET(commands.save) =
            "Сохранить<br>"
            "Использование: save";
        SET(commands.about) =
            "Вывести информацию об игре<br>"
            "Использование: about";
        SET(commands.version) =
            "Вывести версию игры<br>"
            "Использование: version";
        SET(commands.aboutme) =
            "Вывести информацию о текущем пользователе<br>"
            "Использование: aboutme";
        SET(commands.autosave) =
            "Установить и получить период автосохранения<br>"
            "Использование:<br>"
            "\tautosave - получить период автосохранения<br>"
            "\tautosave 60 - установить период автосохранения в 60 минут";
        SET(commands.logging) =
            "Установить и получить уровень логов<br>"
            "Использование:<br>"
            "\tlogging - получить уровень логов<br>"
            "\tlogging debug - установить уровень логов в ОТЛАДКА<br>"
            "\tlogging release - установить уровень логов в ВЫПУСК";
        SET(commands.language) =
            "Установить и получить язык<br>"
            "Использование:<br>"
            "\tlanguage - получить язык<br>"
            "\tlanguage en - установить язык в АНГЛИЙСКИЙ<br>"
            "\tlanguage ru - установить язык в РУССКИЙ";
        SET(commands.location) =
            "Перейти в локации<br>"
            "Использование:<br>"
            "\tlocation - узнать текущую локацию<br>"
            "\tlocation &lt;location name&gt; - перейти в конкретную локацию";
        SET(commands.privilege) =
            "Вывести уровень привилегий текущего пользователя<br>"
            "Использование: privilege";
        SET(commands.market) =
            "Посетить рынок<br>"
            "Использование:<br>"
            "\tmarket - получить список сделок на рынке";
        SET(commands.su) =
            "Переключить уровень привилегий (общий, супер)<br>"
            "Использование: su";
        SET(commands.clear) =
            "Очистить окно консоли<br>"
            "Использование: clear";
        SET(commands.inventory) =
            "Показать инвентарь игрока<br>"
            "Использование: inventory";
        SET(commands.give) =
            "Выдать пользователю предмет<br>"
            "Использование: give &lt;ID предмета&gt; &lt;количество&gt;<br>"
            "Только для суперпользователей!";
        SET(commands.experience) =
            "Изменить количество опыта у пользователя<br>"
            "Использование: experience &lt;количество опыта&gt;<br>"
            "Только для суперпользователей!";
        SET(commands.rating) =
            "Показать рейтинг пользователей<br>"
            "Использование: rating";
        SET(commands.exit) =
            "Выйти из игры<br>"
            "Использование: exit";
        SET(commands.time) =
            "Вывести текущее время<br>"
            "Использование: time";
        SET(commands.help) =
            "Вывести список всех команд<br>"
            "Использование: help";
        SET(commands.man) =
            "Вывести мануал для команды<br>"
            "Использование: man &lt;команда1&gt; &lt;команда2&gt; ...";

        SET(stats["stats.got"]) = "Получено";
        SET(stats["stats.sold"]) = "Продано";
        SET(stats["stats.bought"]) = "Куплено";
        SET(stats["stats.caught"]) = "Поймано";

        SET(locations["location.volga"]) = "Волга";
        SET(locations["location.oka"]) = "Ока";

        languages[Language::Russian].second = updatesCount;
        break;
    } default: {
        this->game->logger.error("Unknown language");
        break;
    }
    }

    if (!initialSetup) {
        game->aboutMenu.setWindowTitle(fishingTime + ": " + about);
        game->aboutMenu.setWindowIcon(QIcon(Config::imagesDirectory + "icon.png"));
        game->console.setWindowTitle(fishingTime + ": " + console);
        game->console.setWindowIcon(QIcon(Config::imagesDirectory + "icon.png"));
        game->setWindowTitle(fishingTime);
        game->gameMenu.getPopUpInventoryTable().setWindowTitle(fishingTime + ": " + inventory);
        game->gameMenu.getPopUpInventoryTable().setWindowIcon(QIcon(Config::imagesDirectory + "icon.png"));
        game->logger.info("Set language: " + QString::number((int)l));
    }
}
