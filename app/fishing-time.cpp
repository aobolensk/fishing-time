#include <QApplication>
#include <QElapsedTimer>
#include <csignal>
#include "game.h"
#include "errorwidget.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc == 2 && !strcmp(argv[1], "--err")) {
        QApplication app(argc, argv);
        QFile errorLog("error.log");
        errorLog.open(QIODevice::ReadOnly);
        QTextStream f(&errorLog);
        QString buffer;
        buffer = f.readLine();
        ErrorWidget error;
        error.setErrorLabel(buffer);
        buffer = f.readAll();
        error.setErrorText(buffer);
        error.show();
        return app.exec();
    }
    signal(SIGSEGV, ErrorWidget::signalHandler);
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
