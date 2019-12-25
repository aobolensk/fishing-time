#include <QApplication>
#include <QElapsedTimer>
#include <csignal>
#include "game.h"
#include "errorwidget.h"

void errorWindow(int signum) {
    ErrorWidget error;
    error.show();
    QApplication::exec();
    exit(signum);
}

int main(int argc, char *argv[]) {
    signal(SIGSEGV, errorWindow);
    QApplication app(argc, argv);
    QString config = "config.json";
    if (argc >= 2)
        config = argv[1];
    QElapsedTimer timer;
    timer.start();
    Game game(nullptr, config);
    game.logger.info("Game loaded in " + QString::number(timer.elapsed()) + " milliseconds");
    game.show();
    return app.exec();
}
