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
            (void) args;
            game->hideCurrentMenu();
            game->loginMenu.display();
            log.info("Moved to login menu");
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.login
    };

    commands["signup"] = {
        [&](QStringList &args) -> int {
            (void) args;
            game->hideCurrentMenu();
            game->signupMenu.display();
            log.info("Moved to signup menu");
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.signup
    };

    commands["click"] = {
        [&](QStringList &args) -> int {
            (void) args;
            if (game->activeUser == -1) {
                log.error("You are not logged in");
            } else {
                log.info("Click performed");
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
                log.error("You're already logged out");
            } else {
                game->hideCurrentMenu();
                game->gameMenu.logOutFunction();
                game->mainMenu.display();
                log.info("Successfully logged out");
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.logout
    };

    commands["save"] = {
        [&](QStringList &args) -> int {
            (void) args;
            log.info("Saving...");
            game->manualSave();
            log.info("Saving is complete");
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.save
    };

    commands["about"] = {
        [&](QStringList &args) -> int {
            (void) args;
            log.writeln(game->str.aboutDescription.arg(
                "https://github.com/gooddoog/fishing-time/"
            ));
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.about
    };

    commands["settings"] = {
        [&](QStringList &args) -> int {
            if (args.size() < 2) {
                log.error("\"settings\" command requires more args");
                return 1;
            }
            
            if (args[1] == "get") {
                if (args.size() < 3) {
                    log.error("\"settings get\" requires more args");
                    return 1;
                }
                log.writeln(args[2] + " : " + game->settingsMenu.getSetting(args[2]));
            } else {
                log.error("Invalid argument: \"" + args[1] + "\" "
                          "for settings command");
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
                log.writeln("You are guest. Your privilege level: Common (0)");
            } else {
                log.write("Your privilege level: ");
                switch((PrivilegeLevel)game->users[game->activeUser].getPrivilegeLevel()) {
                case PrivilegeLevel::Common:
                    log.writeln("Common (0)");
                    break;
                case PrivilegeLevel::Super:
                    log.writeln("Super (1)");
                    break;
                }
            }
            return 0;
        },
        PrivilegeLevel::Common,
        &game->str.commands.privilege
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

    commands["help"] = {
        [&](QStringList &args) -> int {
            (void) args;
            log.writeln("List of all existing commands:");
            for (auto command : commands.keys())  {
                log.writeln(command);
            }
            log.writeln("Use 'man &lt;command&gt;' to get description");
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
                    log.error("Command " + args[i] + " does not exist");
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
