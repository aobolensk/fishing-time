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
}

void Console::commandParser() {
    if (input.text().count() == 0)
        return;
    log.writeln("> " + input.text());
    QStringList args = input.text().split(" ", QString::SplitBehavior::SkipEmptyParts);
    if (args[0] == "echo") {
        for (int i = 1; i < args.count(); ++i) {
            log.write(args[i]);
        }
        log.writeln("");
    } else if (args[0] == "exit") {
        QApplication::quit();
    } else {
        log.error("Unknown command: " + args[0]);
    }
}

void Console::display() {
    this->show();
}

void Console::hide() {
    this->QWidget::hide();
}
