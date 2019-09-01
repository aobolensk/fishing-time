#include <QScrollBar>
#include <QSettings>
#include <QDialog>
#include "console.h"
#include "game.h"

Console::Console(Game *game) :
    QWidget(),
    game(game),
    grid(QGridLayout(this)),
    log(game, &console) {
    QSettings settings;
    if (!this->restoreGeometry(settings.value("consoleGeometry").toByteArray())) {
        qDebug() << "Unable to restore console window geometry. Loading defaults...";
        this->setGeometry(QRect(QPoint(740, 100), QSize(360, 480)));
    }
    this->setLayout(&grid);

    grid.addWidget(&console, 0, 0);
    console.setReadOnly(true);

    grid.addWidget(&input, 1, 0);
    QObject::connect(&input, &QLineEdit::returnPressed, [this]() {
        commandParser();
        input.clear();
        console.verticalScrollBar()->setValue(console.verticalScrollBar()->maximum());
    });

    input.installEventFilter(this);

    registerCommands();
}

void Console::InputHistory::push(const QString &str) {
    while (index != buffer.size() - 1)
        buffer.pop_back();
    buffer.push_back(str);
    ++index;
    afterPush = true;
    qDebug() << "push index:" << index;
}

QString Console::InputHistory::getUpper() {
    if (afterPush) {
        afterPush = false;
    } else if (index > 0) {
        --index;
    }
    qDebug() << "getUpper index:" << index;
    return buffer[index];
}

QString Console::InputHistory::getLower() {
    if (index < buffer.size() - 1)
        ++index;
    if (index == buffer.size())
        return "";
    qDebug() << "getLower index:" << index;
    return buffer[index];
}

bool Console::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if (key->key() == 16777235) { // arrow up
            input.setText(inputHistory.getUpper());
        } else if (key->key() == 16777237) { // arrow down
            input.setText(inputHistory.getLower());
        }
        qDebug() << key->key();
    }
    return QObject::eventFilter(obj, event);
}

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
        "Print arguments<br>"
        "Usage: echo &lt;argument1&gt; &lt;argument2&gt; ..."
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
        "Go to login menu"
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
        "Go to sign up menu"
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
        "Log out and go to main menu"
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
        "Save"
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
        "Print information about this game"
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
        "Exit from the game"
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
                log.writeln(commandIterator->description);
            }
            return 0;
        },
        PrivilegeLevel::Common,
        "Print manual for commands<br>"
        "Usage: man &lt;command1&gt; &lt;command2&gt; ..."
    };
}

void Console::parse(QStringList &args) {
    auto commandIterator = commands.find(args[0]);
    if (commandIterator != commands.end()) {
        if (commandIterator->privilege <= PrivilegeLevel::Common) {
            int retCode = commandIterator->function(args);
            if (retCode != 0) {
                log.error("Command " + args[0] +
                        " returned " + QString::number(retCode));
            }
        } else {
            log.error("You do not have permission to perform command " + args[0]);
        }
    } else {
        log.error("Unknown command: " + args[0]);
    }
}

void Console::commandParser() {
    if (input.text().count() == 0)
        return;
    inputHistory.push(input.text());
    log.writeln("> " + input.text());
    QStringList args = input.text().split(" ", QString::SplitBehavior::SkipEmptyParts);
    parse(args);
}

void Console::display() {
    this->setWindowTitle(game->str.fishingTime + ": " + game->str.console);
    this->show();
}

void Console::hide() {
    this->QWidget::hide();
}
