#include <QScrollBar>
#include <QSettings>
#include "console.h"
#include "game.h"

Console::Console(Game *game) :
    QWidget(),
    game(game),
    grid(QGridLayout(this)),
    log(game, &console) {
    (void) this->game;
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

    registerCommands();
}

void Console::registerCommands() {
    /* Register commands only in this function.
     * Function is defined as mapping from QString
     * to std::function <int(QStringList &args)>
     * Arguments:
     *  args[0] - name of the command
     *  args[1], ... - args for that command
     * Return value:
     *  int - exit code of this command (0 if success)
     */

    commands["echo"] =
    [&](QStringList &args) -> int {
        for (int i = 1; i < args.count(); ++i) {
            log.write(args[i]);
        }
        log.writeln("");
        return 0;
    };

    commands["login"] =
    [&](QStringList &args) -> int {
        (void) args;
        game->hideCurrentMenu();
        game->loginMenu.display();
        log.info("Moved to login menu");
        return 0;
    };

    commands["signup"] =
    [&](QStringList &args) -> int {
        (void) args;
        game->hideCurrentMenu();
        game->signupMenu.display();
        log.info("Moved to signup menu");
        return 0;
    };

    commands["logout"] =
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
    };

    commands["save"] =
    [&](QStringList &args) -> int {
        (void) args;
        log.info("Saving...");
        game->manualSave();
        log.info("Saving is complete");
        return 0;
    };

    commands["quit"] =
    commands["exit"] =
    commands["q"] =
    [&](QStringList &args) -> int {
        (void) args;
        QApplication::quit();
        return 0;
    };
}

void Console::parse(QStringList &args) {
    auto commandIterator = commands.find(args[0]);
    if (commandIterator != commands.end()) {
        int retCode = (*commandIterator)(args);
        if (retCode != 0) {
            log.error("Command " + args[0] +
                      " returned " + QString::number(retCode));
        }
    } else {
        log.error("Unknown command: " + args[0]);
    }
}

void Console::commandParser() {
    if (input.text().count() == 0)
        return;
    log.writeln("> " + input.text());
    QStringList args = input.text().split(" ", QString::SplitBehavior::SkipEmptyParts);
    parse(args);
}

void Console::display() {
    this->show();
}

void Console::hide() {
    this->QWidget::hide();
}
