#include "console.h"
#include "game.h"

void Console::registerCommands() {
    /* Register commands only in this function.
     * Function is defined as mapping from QString
     * to std::function <int(QStringList &args)>
     * It is necessary to add manual string for
     * every added function.
     * Arguments:
     *  args[0] - name of the command
     *  args[1], ... - args for that command
     * Return value:
     *  int - exit code of this command (0 if success)
     */

    commands["echo"] = {
        [&](QStringList &args) -> int {
            for (int i = 1; i < args.count(); ++i) {
                log.write(args[i]);
            }
            log.writeln("");
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.echo
    };

    commands["login"] = {
        [&](QStringList &args) -> int {
            // args[1] -> login
            // args[2] -> password
            if (args.count() != 3) {
                log.error(game->str.invalidArgumentsFormat.arg(args[0]));
                return 1;
            }
            if (game->activeUser != -1) {
                log.error(game->str.youAreAlreadyLoggedIn);
                return 1;
            }
            int userIndex = -1;
            for (int i = 0; i < game->users.size(); ++i) {
                if (game->users[i].getUsername() == args[1]) {
                    userIndex = i;
                    break;
                }
            }
            if (userIndex == -1) {
                log.error(game->str.unknownUser.arg(args[1]));
                return 1;
            }
            if (QCryptographicHash::hash(args[2].toLatin1(), QCryptographicHash::Md5) ==
                    game->users[userIndex].getPasswordHash()) {
                game->activeUser = userIndex;
                game->activeLocation = 0;
                game->hideCurrentMenu();
                game->gameMenu.display();
                game->userTimestamp = QDateTime::currentDateTime();
                log.info(game->str.successfullyLoggedIn.arg(args[1]));
                return 0;
            } else {
                log.error(game->str.incorrectPassword);
                return 1;
            }
        },
        PrivilegeLevel::Common,
        &game->str.commands.login
    };

    commands["signup"] = {
        [&](QStringList &args) -> int {
            // args[1] -> login
            // args[2] -> password
            // args[3] -> password confirmation
            if (args.count() != 4) {
                log.error(game->str.invalidArgumentsFormat.arg(args[0]));
                return 1;
            }
            for (int i = 0; i < game->users.size(); ++i) {
                if (game->users[i].getUsername() == args[1]) {
                    log.error(game->str.thisUserAlreadyExistsText);
                    return 1;
                }
            }
            if (args[2] != args[3]) {
                log.error(game->str.confirmPasswordWarning);
                return 1;
            }
            game->users.push_back(User(args[1], args[2]));
            log.info(game->str.newUserCreatedText.arg(args[1]));
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.signup
    };

    commands["click"] = {
        [&](QStringList &args) -> int {
            (void) args;
            if (game->activeUser == -1) {
                log.error(game->str.youAreNotLoggedIn);
            } else {
                log.info(game->str.click);
                game->gameMenu.clickFunction();
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.click
    };

    commands["logout"] = {
        [&](QStringList &args) -> int {
            (void) args;
            if (game->activeUser == -1) {
                log.error(game->str.youAreNotLoggedIn);
            } else {
                game->hideCurrentMenu();
                game->gameMenu.logOutFunction();
                game->mainMenu.display();
                log.info(game->str.successfullyLoggedOut);
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.logout
    };

    commands["save"] = {
        [&](QStringList &args) -> int {
            (void) args;
            log.info(game->str.saving);
            game->manualSave();
            log.info(game->str.savingIsComplete);
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.save
    };

    commands["about"] = {
        [&](QStringList &args) -> int {
            (void) args;
            log.writeln(game->aboutMenu.getAboutInfo());
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.about
    };

    commands["aboutme"] = {
        [&](QStringList &args) -> int {
            (void) args;
            if (game->activeUser == -1) {
                log.error(game->str.youAreNotLoggedIn);
                return 1;
            }
            log.writeln(game->str.username + ": " +
                game->users[game->activeUser].getUsername());
            log.writeln(game->str.coins + ": " +
                QString::number(game->users[game->activeUser].getCoins()));
            log.writeln(game->str.clicksCount + ": " +
                QString::number(game->users[game->activeUser].getClicks()));
            game->updateTimePlayed();
            log.writeln(game->str.timePlayed + ": " +
                game->users[game->activeUser].getInGameTime());
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.aboutme
    };

    commands["settings"] = {
        [&](QStringList &args) -> int {
            if (args.size() < 2) {
                log.error(game->str.invalidArgumentsFormat.arg(args[0]));
                return 1;
            }
            
            if (args[1] == "get") {
                if (args.size() < 3) {
                    log.error(game->str.invalidArgumentsFormat.arg(args[0]));
                    return 1;
                }
                log.writeln(args[2] + " : " +
                    game->settingsMenu.getSetting(args[2]));
            } else {
                log.error(game->str.invalidArgumentsFormat.arg(args[0]));
                return 1;
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.settings
    };

    commands["privilege"] = {
        [&](QStringList &args) -> int {
            (void) args;
            if (game->activeUser == -1) {
                log.writeln(game->str.youAreNotLoggedIn + ". " + 
                    game->str.yourPrivilegeLevel + ": " +
                    game->str.privilegeLevelCommon);
            } else {
                log.write(game->str.yourPrivilegeLevel + ": ");
                switch((PrivilegeLevel)game->users[game->activeUser].getPrivilegeLevel()) {
                case PrivilegeLevel::Common:
                    log.writeln(game->str.privilegeLevelCommon);
                    break;
                case PrivilegeLevel::Super:
                    log.writeln(game->str.privilegeLevelSuper);
                    break;
                }
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.privilege
    };

    commands["su"] = {
        [&](QStringList &args) -> int {
            (void) args;
            if (game->activeUser == -1) {
                log.error(game->str.youAreNotLoggedIn);
                return 1;
            }
            switch ((PrivilegeLevel)game->users[game->activeUser].getPrivilegeLevel()) {
            case PrivilegeLevel::Common:
                game->users[game->activeUser].setPrivilegeLevel((int)PrivilegeLevel::Super);
                log.writeln(game->str.yourPrivilegeLevel + ": " +
                    game->str.privilegeLevelSuper);
                break;
            case PrivilegeLevel::Super:
                game->users[game->activeUser].setPrivilegeLevel((int)PrivilegeLevel::Common);
                log.writeln(game->str.yourPrivilegeLevel + ": " +
                    game->str.privilegeLevelCommon);
                break;
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.clear
    };

    commands["clear"] = {
        [&](QStringList &args) -> int {
            (void) args;
            console.clear();
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.clear
    };

    commands["inventory"] = {
        [&](QStringList &args) -> int {
            (void) args;
            if (game->activeUser == -1) {
                log.error(game->str.youAreNotLoggedIn);
                return 1;
            }
            QMap<QString, int>::const_iterator it =
                game->users[game->activeUser].inventory.get().constBegin();
            QMap<QString, int>::const_iterator invEnd =
                game->users[game->activeUser].inventory.get().constEnd();
            log.writeln(game->str.inventory + ':');
            while (it != invEnd) {
                log.writeln(game->str.getItemName(it.key()) + ": " +
                    QString::number(it.value()));
                ++it;
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.inventory
    };

    commands["quit"] =
    commands["exit"] =
    commands["q"] = {
        [&](QStringList &args) -> int {
            (void) args;
            QApplication::quit();
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.exit
    };

    commands["time"] = {
        [&](QStringList &args) -> int {
            (void) args;
            log.writeln(QDateTime::currentDateTime().toString(Qt::ISODate));
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.time
    };

    commands["help"] = {
        [&](QStringList &args) -> int {
            (void) args;
            log.writeln(game->str.listOfAllCommands + ":");
            log.write("[ ");
            bool needSpace = false;
            for (auto command : commands.keys())  {
                if (!needSpace) {
                    needSpace = true;
                } else {
                    log.write(", ");
                }
                log.write(command + ' ');
            }
            log.writeln("]");
            log.writeln(game->str.useManToGetDescription);
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.help
    };

    commands["man"] = {
        [&](QStringList &args) -> int {
            for (int i = 1; i < args.count(); ++i) {
                auto commandIterator = commands.find(args[i]);
                if (commandIterator == commands.end()) {
                    log.error(game->str.unknownCommand.arg(args[i]));
                    return 1;
                }
                log.writeln(args[i] + ":");
                log.writeln(*(commandIterator->description));
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.man
    };
}
