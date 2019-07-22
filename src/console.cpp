#include <QScrollBar>
#include "console.h"
#include "game.h"

Console::Console(Game *game) :
    QWidget(),
    game(game),
    grid(QGridLayout(this)),
    log(&console) {
    (void) this->game;
    this->setGeometry(QRect(QPoint(740, 100), QSize(360, 480)));
    this->setLayout(&grid);

    grid.addWidget(&console, 0, 0);
    console.setReadOnly(true);

    grid.addWidget(&input, 1, 0);
    QObject::connect(&input, &QLineEdit::returnPressed, [this]() {
        commandParser();
        input.clear();
        console.verticalScrollBar()->setValue(console.verticalScrollBar()->maximum());
    });

    this->display();
}

void Console::commandParser() {
    if (input.text().count() == 0)
        return;
    log.info("> " + input.text());
    QStringList args = input.text().split(" ", QString::SplitBehavior::SkipEmptyParts);
    if (args[0] == "echo") {
        for (int i = 1; i < args.count(); ++i) {
            log.info(args[i] + ' ', false);
        }
        log.info("");
    } else if (args[0] == "exit") {
        QApplication::quit();
    } else {
        log.error("[ERROR] Unknown command: " + args[0]);
    }
}

void Console::display() {
    this->show();
}

void Console::hide() {
    this->QWidget::hide();
}

Console::Log::Log(QTextEdit *field) :
    console(field) {}

void Console::Log::info(const QString &message, bool newLine) {
    console->insertHtml(message);
    if (newLine)
        console->append("");
}

void Console::Log::warning(const QString &message, bool newLine) {
    console->insertHtml("<font color=\"orange\">" + message + "</font>");
    if (newLine)
        console->append("");
}

void Console::Log::error(const QString &message, bool newLine) {
    console->insertHtml("<font color=\"red\">" + message + "</font>");
    if (newLine)
        console->append("");
}
