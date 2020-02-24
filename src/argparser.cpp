#include <csignal>
#include <QElapsedTimer>
#include <QSettings>
#include "argparser.h"
#include "errorwidget.h"
#include "game.h"

ArgParser::ArgParser() :
        errorOption(QStringList() << "e" << "err" << "error", "Shows last error message."),
        resetOption(QStringList() << "r" << "reset", "Resets game settings.") {
    qParser.addHelpOption();
    qParser.addVersionOption();
    qParser.addOption(errorOption);
    qParser.addOption(resetOption);
}

int ArgParser::process() {
    qParser.process(*qApp);
    if (qParser.isSet(errorOption)) {
        return ErrorWidget::launchViewer();
    }
    if (qParser.isSet(resetOption)) {
        QSettings settings;
        settings.clear();
        return 0;
    }
    signal(SIGSEGV, ErrorWidget::signalHandler);
    QString config = "config.json";
    QElapsedTimer timer;
    timer.start();
    Game game(nullptr, config);
    game.logger.info("Game loaded in " + QString::number(timer.elapsed()) + " milliseconds");
    game.show();
    return qApp->exec();
}
