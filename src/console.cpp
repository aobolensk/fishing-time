#include <QScrollBar>
#include <QSettings>
#include <QDialog>
#include <QMutex>
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
        QMutex mutex;
        mutex.lock();
        commandParser();
        input.clear();
        console.verticalScrollBar()->setValue(console.verticalScrollBar()->maximum());
        mutex.unlock();
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

int Console::parseCommand(QStringList &args) {
    auto commandIterator = commands.find(args[0]);
    int retCode = 0;
    if (commandIterator != commands.end()) {
        if ((game->activeUser == -1 && commandIterator->privilege <= PrivilegeLevel::Common) ||
            (game->activeUser != -1 && commandIterator->privilege <= (PrivilegeLevel)game->users[game->activeUser].getPrivilegeLevel())) {
            retCode = commandIterator->function(args);
            if (retCode != 0) {
                log.error("Command " + args[0] +
                        " returned " + QString::number(retCode));
            }
        } else {
            log.error("You do not have permission to perform command " + args[0]);
        }
    } else {
        retCode = -1;
        log.error("Unknown command: " + args[0]);
    }
    return retCode;
}

void Console::parse(QStringList &args) {
    QStringList command;
    for (int i = 0; i < args.count(); ++i) {
        if (args[i][args[i].count() - 1] == ';') {
            QString word = args[i];
            word.chop(1);
            if (word.count()) {
                command.append(word);
            }
            parseCommand(command);
            command.clear();
        } else if (args[i] == "&&") {
            int retCode = parseCommand(command);
            command.clear();
            if (retCode != 0) {
                break;
            }
        } else {
            command.append(args[i]);
        }
    }
    if (command.count() > 0) {
        parseCommand(command);
    }
}

void Console::commandParser() {
    QStringList args = input.text().split(" ", QString::SplitBehavior::SkipEmptyParts);
    if (args.size() == 0) {
        input.clear();
        return;
    }
    log.writeln("> " + input.text());
    inputHistory.push(input.text());
    parse(args);
}

void Console::display() {
    this->setWindowTitle(game->str.fishingTime + ": " + game->str.console);
    this->show();
}

void Console::hide() {
    this->QWidget::hide();
}
