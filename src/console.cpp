#include <QApplication>
#include <QDialog>
#include <QMessageBox>
#include <QMutex>
#include <QScrollBar>
#include <QSettings>
#include "console.h"
#include "game.h"

Console::Console(Game *game) :
    Menu(game, nullptr, true),
    log(game, &console) {
    QSettings settings;
    if (!this->restoreGeometry(settings.value("consoleGeometry").toByteArray())) {
        qDebug() << "Unable to restore console window geometry. Loading defaults...";
        this->setGeometry(QRect(QPoint(740, 100), QSize(360, 480)));
    }
    this->setLayout(grid);

    grid->addWidget(&jumpToBottomButton, 0, 0, 1, 6);
    jumpToBottomButton.setVisible(false);
    jumpToBottomButton.setEnabled(false);
    QObject::connect(&jumpToBottomButton, &QPushButton::clicked, [this]() {
        jumpToBottomFunction();
    });

    grid->addWidget(&console, 1, 0, 1, 6);
    console.setReadOnly(true);

    grid->addWidget(&input, 2, 0, 1, 5);
    QObject::connect(&input, &QLineEdit::returnPressed, [this]() {
        enterCommandFunction();
    });

    grid->addWidget(&enterButton, 2, 5, 1, 1);
    enterButton.setVisible(false);
    enterButton.setEnabled(false);
    QObject::connect(&enterButton, &QPushButton::clicked, [this]() {
        enterCommandFunction();
    });

    input.setFocus();

    input.installEventFilter(this);
    console.installEventFilter(this);

    registerCommands();
}

void Console::InputHistory::reset() {
    index = buffer.size();
    qDebug() << "reset:" << index;
}

void Console::InputHistory::push(const QString &str) {
    while (buffer.size() >= Config::MAX_INPUT_HISTORY_SIZE)
        buffer.pop_front();
    buffer.push_back(str);
    index = buffer.size();
    qDebug() << "push index:" << index;
}

QString Console::InputHistory::getUpper() {
    if (index > 0)
        --index;
    qDebug() << "getUpper index:" << index;
    return buffer[index];
}

QString Console::InputHistory::getLower() {
    if (index <= buffer.size() - 1)
        ++index;
    if (index == buffer.size())
        return "";
    qDebug() << "getLower index:" << index;
    return buffer[index];
}

void Console::closeEvent(QCloseEvent *event) {
    if (game->isHidden() && game->logger.isHidden()) {
        game->console.hide();
        game->logger.hide();
        QMessageBox::StandardButton closeResult =
            QMessageBox::question(this, game->str.fishingTime, game->str.exitConfirmation,
            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
        if (closeResult != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
            QApplication::quit();
        }
    } else {
        this->hide();
    }
}

bool Console::eventFilter(QObject *obj, QEvent *event) {
    if (this->isHidden()) return false;
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *key = static_cast<QKeyEvent *>(event);
        if (key->key() == 16777235) { // arrow up
            input.setText(inputHistory.getUpper());
        } else if (key->key() == 16777237) { // arrow down
            input.setText(inputHistory.getLower());
        }
        qDebug() << key->key();
    }
    if (console.verticalScrollBar()->value() == console.verticalScrollBar()->maximum()) {
        jumpToBottomButton.hide();
    } else {
        jumpToBottomButton.show();
    }
    return QObject::eventFilter(obj, event);
}

void Console::jumpToBottomFunction() {
    console.verticalScrollBar()->setValue(console.verticalScrollBar()->maximum());
}

void Console::enterCommandFunction() {
    QMutex mutex;
    mutex.lock();
    this->commandParser();
    input.clear();
    console.verticalScrollBar()->setValue(console.verticalScrollBar()->maximum());
    mutex.unlock();
}

int Console::parseCommand(QStringList &args) {
    auto commandIterator = commands.find(args[0]);
    if (args[0] == "login" ||
        args[0] == "signup" ||
        args[0] == "password" ||
        args[0] == "delete_account") {
        inputHistory.needToPush = false;
    }
    int retCode = 0;
    if (commandIterator != commands.end()) {
        if ((game->activeUser == -1 && commandIterator->privilege <= PrivilegeLevel::Common) ||
            (game->activeUser != -1 && commandIterator->privilege <= (PrivilegeLevel)game->users[game->activeUser].getPrivilegeLevel())) {
            retCode = commandIterator->function(args);
            if (retCode != 0) {
                log.error(game->str.commandReturned.arg(
                    args[0],
                    QString::number(retCode)
                ));
            }
        } else {
            log.error(game->str.permissionError.arg(args[0]));
        }
    } else {
        retCode = -1;
        log.error(game->str.unknownCommand.arg(args[0]));
    }
    return retCode;
}

void Console::parse(QStringList &args) {
    inputHistory.needToPush = true;
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
        } else if (args[i] == "||") {
            int retCode = parseCommand(command);
            command.clear();
            if (retCode == 0) {
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
        inputHistory.reset();
        input.clear();
        return;
    }
    QStringList argsCopy(args);
    for (int i = 0; i < argsCopy.size();) {
        if (argsCopy[i] == "login" ||
            argsCopy[i] == "signup") {
            ++i;
            while (i < argsCopy.size() && argsCopy[i] != "&&" && argsCopy[i][argsCopy[i].size() - 1] != ';') {
                for (int j = 0; j < argsCopy[i].size(); ++j) {
                    argsCopy[i][j] = '*';
                }
                ++i;
            }
        } else {
            ++i;
        }
    }
    QString command;
    for (int i = 0; i < argsCopy.size(); ++i) {
        command += argsCopy[i] + ' ';
    }
    log.writeln("> " + command);
    parse(args);
    if (inputHistory.needToPush) {
        inputHistory.push(input.text());
    }
}

void Console::display() {
    this->setWindowTitle(game->str.fishingTime + ": " + game->str.console);
    this->setWindowIcon(QIcon(Config::imagesDirectory + "icon.png"));
    this->show();

    jumpToBottomButton.setText(game->str.jumpToBottom);
    jumpToBottomButton.setVisible(true);
    jumpToBottomButton.setEnabled(true);

    enterButton.setText(game->str.enter);
    enterButton.setVisible(true);
    enterButton.setEnabled(true);

    displayed = true;
}

void Console::hide() {
    this->QWidget::hide();

    jumpToBottomButton.setVisible(false);
    jumpToBottomButton.setEnabled(false);

    enterButton.setVisible(false);
    enterButton.setEnabled(false);

    displayed = false;
}
